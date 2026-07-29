plugins {
    id("java-library")
}

val useRepoLibs = rootProject.extra["samplesUseRepoLibs"] as Boolean

dependencies {
    if(useRepoLibs) {
        compileOnly(libs.jjoltCore)
    }
    else {
        compileOnly(project(":jolt:core"))
    }
    compileOnly(libs.fdxJoltExt)

    api(libs.fdxApplication)
    api(libs.fdxDisplay)
    api(libs.fdxGraphics)
    api(libs.fdxG3d)
    api(libs.fdxAssetManager)
}

java {
    sourceCompatibility = JavaVersion.toVersion(libs.versions.javaFfmTarget.get())
    targetCompatibility = JavaVersion.toVersion(libs.versions.javaFfmTarget.get())
}
