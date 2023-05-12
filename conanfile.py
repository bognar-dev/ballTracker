from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake
from conan.tools.microsoft import MSBuildToolchain, MSBuildDeps, MSBuild
class Conan(ConanFile):

        name = "BallTracking"
        description = "BallTracking with OpenCV"
        #options = {"shared": [True, False]}
        settings = "os", "compiler", "build_type", "arch"
        generators = "CMakeToolchain", "CMakeDeps"

        def requirements(self):
            self.requires("opencv/4.1.2")

        def build(self):
            cmake = CMake(self)
            cmake.configure()
            cmake.build()

        def imports(self):
            self.copy("*.dll", "bin", "bin")

        def package(self):
            out_dir = "./out"

            print("Source Path: " + os.getcwd() + out_dir)

            self.output.info("Copying header files...")
            self.copy("*h", dst="include", src=out_dir, keep_path=False)

            self.output.info("Copying libs...")
            self.copy("*.lib", dst="lib", src=out_dir, keep_path=False)
            self.copy("*.so", dst="lib", src=out_dir, keep_path=False)

            self.output.info("Copying runtime...")
            self.copy("*.dll", dst="bin", src=out_dir, keep_path=False)
            self.copy("*.exe", dst="bin", src=out_dir, keep_path=False)

            self.output.info("Copying documentation...")
            self.copy("*", dst="doc", src=out_dir +"/doc", keep_path=False)
