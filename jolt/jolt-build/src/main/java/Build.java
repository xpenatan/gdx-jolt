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
        windowsTarget.cppFlags.add("-DJPH_ENABLE_ASSERTS");
        windowsTarget.cppFlags.add("-DJPH_CROSS_PLATFORM_DETERMINISTIC");
        windowsTarget.cppFlags.add("-DJPH_OBJECT_LAYER_BITS=32");
        multiTarget.add(windowsTarget);

        // Compile glue code and link
        WindowsTarget linkTarget = new WindowsTarget();
        linkTarget.addJNIHeaders();
        linkTarget.headerDirs.add("-I" + libBuildCPPPath + "/src/jolt/");
        linkTarget.linkerFlags.add(libBuildCPPPath + "/libs/windows/jolt64.a");
        linkTarget.cppInclude.add(libBuildCPPPath + "/src/jniglue/JNIGlue.cpp");
        linkTarget.cppFlags.add("-DJPH_ENABLE_ASSERTS");
        linkTarget.cppFlags.add("-DJPH_CROSS_PLATFORM_DETERMINISTIC");
        linkTarget.cppFlags.add("-DJPH_OBJECT_LAYER_BITS=32");
        multiTarget.add(linkTarget);

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
        linuxTarget.cppFlags.add("-DJPH_ENABLE_ASSERTS");
        linuxTarget.cppFlags.add("-DJPH_CROSS_PLATFORM_DETERMINISTIC");
        linuxTarget.cppFlags.add("-DJPH_OBJECT_LAYER_BITS=32");
        multiTarget.add(linuxTarget);

        // Compile glue code and link
        LinuxTarget linkTarget = new LinuxTarget();
        linkTarget.addJNIHeaders();
        linkTarget.headerDirs.add("-I" + libBuildCPPPath + "/src/jolt/");
        linkTarget.linkerFlags.add(libBuildCPPPath + "/libs/linux/libjolt64.a");
        linkTarget.cppInclude.add(libBuildCPPPath + "/src/jniglue/JNIGlue.cpp");
        linkTarget.cppFlags.add("-DJPH_ENABLE_ASSERTS");
        linkTarget.cppFlags.add("-DJPH_CROSS_PLATFORM_DETERMINISTIC");
        linkTarget.cppFlags.add("-DJPH_OBJECT_LAYER_BITS=32");
        multiTarget.add(linkTarget);

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
        macTarget.cppFlags.add("-DJPH_ENABLE_ASSERTS");
        macTarget.cppFlags.add("-DJPH_CROSS_PLATFORM_DETERMINISTIC");
        macTarget.cppFlags.add("-DJPH_OBJECT_LAYER_BITS=32");
        multiTarget.add(macTarget);

        // Compile glue code and link
        MacTarget linkTarget = new MacTarget(isArm);
        linkTarget.addJNIHeaders();
        linkTarget.headerDirs.add("-I" + libBuildCPPPath + "/src/jolt/");
        if(isArm) {
            linkTarget.linkerFlags.add(libBuildCPPPath + "/libs/mac/arm/libjolt64.a");
        }
        else {
            linkTarget.linkerFlags.add(libBuildCPPPath + "/libs/mac/libjolt64.a");
        }
        linkTarget.cppInclude.add(libBuildCPPPath + "/src/jniglue/JNIGlue.cpp");
        linkTarget.cppFlags.add("-DJPH_ENABLE_ASSERTS");
        linkTarget.cppFlags.add("-DJPH_CROSS_PLATFORM_DETERMINISTIC");
        linkTarget.cppFlags.add("-DJPH_OBJECT_LAYER_BITS=32");
        multiTarget.add(linkTarget);

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
        libTarget.cppFlags.add("-DJPH_ENABLE_ASSERTS");
        libTarget.cppFlags.add("-DJPH_CROSS_PLATFORM_DETERMINISTIC");
        libTarget.cppFlags.add("-DJPH_OBJECT_LAYER_BITS=32");
        multiTarget.add(libTarget);

        // Compile glue code and link
        EmscriptenTarget linkTarget = new EmscriptenTarget(idlReader);
        linkTarget.headerDirs.add("-I" + libBuildCPPPath + "/src/jolt");
        linkTarget.headerDirs.add("-include" + libBuildCPPPath + "/src/jolt/JoltCustom.h");
        linkTarget.linkerFlags.add(libBuildCPPPath + "/libs/emscripten/jolt.a");
        linkTarget.cppFlags.add("-DJPH_ENABLE_ASSERTS");
        linkTarget.cppFlags.add("-DJPH_CROSS_PLATFORM_DETERMINISTIC");
        linkTarget.cppFlags.add("-DJPH_OBJECT_LAYER_BITS=32");
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
        androidTarget.cppFlags.add("-DJPH_ENABLE_ASSERTS");
        androidTarget.cppFlags.add("-DJPH_CROSS_PLATFORM_DETERMINISTIC");
        androidTarget.cppFlags.add("-DJPH_OBJECT_LAYER_BITS=32");

        multiTarget.add(androidTarget);
        return multiTarget;
    }
}