#include <opencv2/opencv.hpp>
#include <iostream>
#include <deque>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
    VideoCapture cap("ball_tracking_county.mp4");
    if (!cap.isOpened()) {
        cerr << "ERROR: Unable to open the video file." << endl;
        return -1;
    }

    Mat frame, red, blurred;
    namedWindow("Ball Tracking", WINDOW_NORMAL);

    deque<Point> ball_center_history;  // to store previous center points
    const int history_length = 10;     // number of previous frames to store
    const Scalar ball_color(0, 10, 170);  // color for drawing the ball
    const float gravity = 9.8;  // gravity constant (adjust as needed)

    while (true) {
        bool grabbed = cap.read(frame);
        if (!grabbed) {
            break;
        }

        // Detect the ball
        inRange(frame, Scalar(51, 94, 114), Scalar(96,100 , 185), red);
        imshow("RED",red);
        GaussianBlur(red, blurred, Size(3, 3), 0);

        vector<vector<Point>> contours;
        findContours(blurred, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        if (!contours.empty()) {
            // Find the contour with the largest area
            auto max_it = max_element(contours.begin(), contours.end(),
                                      [](const vector<Point> &lhs, const vector<Point> &rhs) {
                                          return contourArea(lhs) < contourArea(rhs);
                                      });
            auto center = (max_it->at(0) + max_it->at(max_it->size() - 1)) / 2;
            ball_center_history.push_front(center);

            // Draw the ball and its trace
            int thickness = 25;
            for (int i = 0; i < ball_center_history.size() - 1; ++i) {
                line(frame, ball_center_history[i], ball_center_history[i + 1], ball_color, thickness);
            }
            circle(frame, center, 25, ball_color, -1);

            // Predict the ball's path
            float time_step = 1.0 / contours.size();  // adjust the time step based on frame rate
            int predicted_steps = 20;  // number of predicted steps
            Point velocity(0, 0);  // initial velocity (can be modified based on the previous velocities)
            Point predicted_center = center;

            for (int i = 0; i < predicted_steps; ++i) {
                // Apply physics model (assuming constant velocity and gravity)
                predicted_center.x += static_cast<int>(velocity.x * time_step);
                predicted_center.y += static_cast<int>(velocity.y * time_step) +
                                      static_cast<int>((0.5 * gravity * time_step * time_step));

                // Draw the predicted path
                //circle(frame, predicted_center, 25, Scalar(255, 0, 0), -1);

                // Update the velocity (assuming constant vertical acceleration due to gravity)
                velocity.y += static_cast<int>(gravity * time_step);
            }
        }

        imshow("Ball Tracking", frame);
        if (waitKey(1) == 'q') {
            break;
        }

        // Remove the oldest center point if the history becomes too long
        if (ball_center_history.size() > history_length) {
            ball_center_history.pop_back();
        }
    }

}