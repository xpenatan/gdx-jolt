plugins {
    id("com.android.application")
    id("kotlin-android")
}

group = "jolt.example.samples.app.android"

android {
    namespace = "jolt.example.samples.app.android"
    compileSdk = 33

    defaultConfig {
        applicationId = "jolt.example.samples.app.android"
        minSdk = 24
        targetSdk = 33
        versionCode = 1
        versionName = "1.0"
    }

    sourceSets {
        named("main") {
            assets.srcDirs(project.file("../assets"))
            jniLibs.srcDirs("libs")
        }
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(getDefaultProguardFile("proguard-android-optimize.txt"), "proguard-rules.pro")
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_11
        targetCompatibility = JavaVersion.VERSION_11
    }
    kotlinOptions {
        jvmTarget = "11"
    }
}
val natives: Configuration by configurations.creating

dependencies {
    coreLibraryDesugaring("com.android.tools:desugar_jdk_libs:2.0.3")

    if(LibExt.exampleUseRepoLibs) {
        implementation("com.github.xpenatan.gdx-jolt:jolt-android:-SNAPSHOT")
    }
    else {
        implementation(project(":jolt:jolt-android"))
    }

    implementation("com.badlogicgames.gdx:gdx:${LibExt.gdxVersion}")
    implementation("com.badlogicgames.gdx:gdx-backend-android:${LibExt.gdxVersion}")
    natives("com.badlogicgames.gdx:gdx-platform:${LibExt.gdxVersion}:natives-armeabi-v7a")
    natives("com.badlogicgames.gdx:gdx-platform:${LibExt.gdxVersion}:natives-arm64-v8a")
    natives("com.badlogicgames.gdx:gdx-platform:${LibExt.gdxVersion}:natives-x86_64")
    natives("com.badlogicgames.gdx:gdx-platform:${LibExt.gdxVersion}:natives-x86")

    implementation(project(":examples:SamplesApp:core"))
}


tasks.register("copyAndroidNatives") {
    group = "basic-android"
    doFirst {
        natives.files.forEach { jar ->
            val outputDir = file("libs/" + jar.nameWithoutExtension.substringAfterLast("natives-"))
            outputDir.mkdirs()
            copy {
                from(zipTree(jar))
                into(outputDir)
                include("*.so")
            }
        }
    }
}

tasks.whenTaskAdded {
    if ("package" in name) {
        dependsOn("copyAndroidNatives")
    }
}