import org.gradle.api.file.RelativePath
import java.net.URL
import java.nio.file.Files
import java.nio.file.StandardCopyOption

plugins {
    id("java")
}

val buildDirFile = layout.buildDirectory.get().asFile
val joltSourceRoot = buildDirFile.resolve("jolt-source")
val joltArchiveFile = buildDirFile.resolve("tmp/jolt-source.zip")
val joltSourceVersion = libs.versions.joltSource.get()

fun downloadAndExtract(url: String, archiveFile: File, outputDir: File) {
    println("URL: $url")
    delete(outputDir)
    archiveFile.parentFile.mkdirs()
    URL(url).openStream().use { input ->
        Files.copy(input, archiveFile.toPath(), StandardCopyOption.REPLACE_EXISTING)
    }
    copy {
        from(zipTree(archiveFile)) {
            eachFile {
                val strippedSegments = relativePath.segments.drop(1)
                if(strippedSegments.isEmpty()) {
                    exclude()
                }
                else {
                    relativePath = RelativePath(!isDirectory, *strippedSegments.toTypedArray())
                }
            }
            includeEmptyDirs = false
        }
        into(outputDir)
    }
    delete(archiveFile)
}

tasks.register("jolt_download_source") {
    group = "jolt"
    description = "Download the Jolt Physics source tag into the build directory."
    inputs.property("joltSourceVersion", joltSourceVersion)
    outputs.dir(joltSourceRoot)

    doLast {
        downloadAndExtract(
            "https://github.com/jrouwe/JoltPhysics/archive/refs/tags/v$joltSourceVersion.zip",
            joltArchiveFile,
            joltSourceRoot
        )
    }
}
