plugins {
    id("java-library")
}

val useRepoLibs = rootProject.extra["samplesUseRepoLibs"] as Boolean

dependencies {
    implementation(libs.gdxGltfCore)

    if(useRepoLibs) {
        compileOnly(libs.jjoltCore)
        implementation(libs.jjoltGdxGl)
    }
    else {
        compileOnly(project(":jolt:core"))
        implementation(project(":extensions:gdx:gl"))
    }

    implementation(project(":samples:gdx:shared"))
    api(libs.gdxCore)
    implementation(libs.imguiCore)
}

java {
    sourceCompatibility = JavaVersion.toVersion(libs.versions.javaMainTarget.get())
    targetCompatibility = JavaVersion.toVersion(libs.versions.javaMainTarget.get())
}
