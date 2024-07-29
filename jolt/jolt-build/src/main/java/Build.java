import com.github.xpenatan.jparser.builder.BuildMultiTarget;
import com.github.xpenatan.jparser.builder.targets.AndroidTarget;
import com.github.xpenatan.jparser.builder.targets.EmscriptenTarget;
import com.github.xpenatan.jparser.builder.targets.LinuxTarget;
import com.github.xpenatan.jparser.builder.targets.MacTarget;
import com.github.xpenatan.jparser.builder.targets.WindowsTarget;
import com.github.xpenatan.jparser.builder.tool.BuildToolListener;
import com.github.xpenatan.jparser.builder.tool.BuildToolOptions;
import com.github.xpenatan.jparser.builder.tool.BuilderTool;
import com.github.xpenatan.jparser.idl.IDLReader;
import java.util.ArrayList;

public class Build {

    public static void main(String[] args) {
        String libName = "jolt";
        String modulePrefix = "jolt";
        String basePackage = "jolt";
        String sourceDir =  "/build/jolt";
        BuildToolOptions op = new BuildToolOptions(modulePrefix, libName, basePackage, sourceDir, args);
        BuilderTool.build(op, new BuildToolListener() {
            @Override
            public void onAddTarget(BuildToolOptions op, IDLReader idlReader, ArrayList<BuildMultiTarget> targets) {
                if(op.teavm) {
                    targets.add(getTeaVMTarget(op, idlReader));
                }
                if(op.windows64) {
                    targets.add(getWindowTarget(op));
                }
                if(op.linux64) {
                    targets.add(getLinuxTarget(op));
                }
                if(op.mac64) {
                    targets.add(getMacTarget(op, false));
                }
                if(op.macArm) {
                    targets.add(getMacTarget(op, true));
                }
                if(op.android) {
                    targets.add(getAndroidTarget(op));
                }
//                if(op.iOS) {
//                    targets.add(getIOSTarget(op));
//                }
            }
        });
    }

    private static BuildMultiTarget getWindowTarget(BuildToolOptions op) {
        String libBuildCPPPath = op.getModuleBuildCPPPath();

        BuildMultiTarget multiTarget = new BuildMultiTarget();

        // Make a static library
        WindowsTarget windowsTarget = new WindowsTarget();
        windowsTarget.isStatic = true;
        windowsTarget.headerDirs.add("-I" + libBuildCPPPath + "/src/jolt/");
        windowsTarget.cppInclude.add(libBuildCPPPath + "/**/jolt/Jolt/**.cpp");
        multiTarget.add(windowsTarget);

        // Compile glue code and link
        WindowsTarget glueTarget = new WindowsTarget();
        glueTarget.addJNIHeaders();
        glueTarget.headerDirs.add("-I" + libBuildCPPPath + "/src/jolt/");
        glueTarget.linkerFlags.add(libBuildCPPPath + "/libs/windows/jolt64.a");
        glueTarget.cppInclude.add(libBuildCPPPath + "/src/jniglue/JNIGlue.cpp");
        multiTarget.add(glueTarget);

        return multiTarget;
    }

    private static BuildMultiTarget getLinuxTarget(BuildToolOptions op) {
        String libBuildCPPPath = op.getModuleBuildCPPPath();

        BuildMultiTarget multiTarget = new BuildMultiTarget();

        // Make a static library
        LinuxTarget linuxTarget = new LinuxTarget();
        linuxTarget.isStatic = true;
        linuxTarget.headerDirs.add("-I" + libBuildCPPPath + "/src/jolt/");
        linuxTarget.cppInclude.add(libBuildCPPPath + "/**/jolt/Jolt/**.cpp");
        multiTarget.add(linuxTarget);

        // Compile glue code and link
        LinuxTarget glueTarget = new LinuxTarget();
        glueTarget.addJNIHeaders();
        glueTarget.headerDirs.add("-I" + libBuildCPPPath + "/src/jolt/");
        glueTarget.linkerFlags.add(libBuildCPPPath + "/libs/linux/libjolt64.a");
        glueTarget.cppInclude.add(libBuildCPPPath + "/src/jniglue/JNIGlue.cpp");
        multiTarget.add(glueTarget);

        return multiTarget;
    }

    private static BuildMultiTarget getMacTarget(BuildToolOptions op, boolean isArm) {
        String libBuildCPPPath = op.getModuleBuildCPPPath();

        BuildMultiTarget multiTarget = new BuildMultiTarget();

        // Make a static library
        MacTarget macTarget = new MacTarget(isArm);
        macTarget.isStatic = true;
        macTarget.headerDirs.add("-I" + libBuildCPPPath + "/src/jolt/");
        macTarget.cppInclude.add(libBuildCPPPath + "/**/jolt/Jolt/**.cpp");
        multiTarget.add(macTarget);

        // Compile glue code and link
        MacTarget glueTarget = new MacTarget(isArm);
        glueTarget.addJNIHeaders();
        glueTarget.headerDirs.add("-I" + libBuildCPPPath + "/src/jolt/");
        if(isArm) {
            glueTarget.linkerFlags.add(libBuildCPPPath + "/libs/mac/arm/libjolt4.a");
        }
        else {
            glueTarget.linkerFlags.add(libBuildCPPPath + "/libs/mac/libjolt64.a");
        }
        glueTarget.cppInclude.add(libBuildCPPPath + "/src/jniglue/JNIGlue.cpp");
        multiTarget.add(glueTarget);

        return multiTarget;
    }

    private static BuildMultiTarget getTeaVMTarget(BuildToolOptions op, IDLReader idlReader) {
        String libBuildCPPPath = op.getModuleBuildCPPPath();

        BuildMultiTarget multiTarget = new BuildMultiTarget();

        // Make a static library
        EmscriptenTarget libTarget = new EmscriptenTarget(idlReader);
        libTarget.isStatic = true;
        libTarget.compileGlueCode = false;
        libTarget.headerDirs.add("-I" + libBuildCPPPath + "/src/jolt");
        libTarget.cppInclude.add(libBuildCPPPath + "/**/jolt/Jolt/**.cpp");
        multiTarget.add(libTarget);

        // Compile glue code and link
        EmscriptenTarget linkTarget = new EmscriptenTarget(idlReader);
        linkTarget.headerDirs.add("-include" + libBuildCPPPath + "/src/jolt/JoltCustom.h");
        linkTarget.linkerFlags.add(libBuildCPPPath + "/libs/emscripten/jolt.a");
        multiTarget.add(linkTarget);

        return multiTarget;
    }

    private static BuildMultiTarget getAndroidTarget(BuildToolOptions op) {
        String libBuildCPPPath = op.getModuleBuildCPPPath();

        BuildMultiTarget multiTarget = new BuildMultiTarget();

        AndroidTarget androidTarget = new AndroidTarget();
        androidTarget.addJNIHeaders();
        androidTarget.headerDirs.add(libBuildCPPPath + "/src/jolt");
        androidTarget.cppInclude.add(libBuildCPPPath + "/**/jolt/Jolt/**.cpp");
        androidTarget.cppFlags.add("-Wno-error=format-security");
        multiTarget.add(androidTarget);
        return multiTarget;
    }
}