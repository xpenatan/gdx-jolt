plugins {
    id("java-library")
}

val examplesUseMavenArtifacts = rootProject.extra["examplesUseMavenArtifacts"] as Boolean

dependencies {
    implementation(libs.gdxCore)
    api(libs.imguiGdxShared)

    if(examplesUseMavenArtifacts) {
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
