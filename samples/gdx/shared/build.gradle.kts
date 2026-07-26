plugins {
    id("java-library")
}

val useRepoLibs = rootProject.extra["samplesUseRepoLibs"] as Boolean

dependencies {
    implementation(libs.gdxCore)
    api(libs.imguiGdxShared)

    if(useRepoLibs) {
        compileOnly(libs.jjoltCore)
        implementation(libs.jjoltGdxGl)
    }
    else {
        compileOnly(project(":jolt:core"))
        implementation(project(":extensions:gdx:gl"))
    }
}

java {
    sourceCompatibility = JavaVersion.toVersion(libs.versions.javaMainTarget.get())
    targetCompatibility = JavaVersion.toVersion(libs.versions.javaMainTarget.get())
}
