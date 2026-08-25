plugins {
    id("java-library")
}

val examplesUseMavenArtifacts = rootProject.extra["examplesUseMavenArtifacts"] as Boolean

dependencies {
    api(project(":samples:gdx:shared"))

    implementation(libs.gdxCore)
    api(libs.imguiGdxGl)
    if(examplesUseMavenArtifacts) {
        api(libs.jjoltGdxGl)
    }
    else {
        api(project(":extensions:gdx:gl"))
    }
}

java {
    sourceCompatibility = JavaVersion.toVersion(libs.versions.javaMainTarget.get())
    targetCompatibility = JavaVersion.toVersion(libs.versions.javaMainTarget.get())
}
