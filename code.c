#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256
#define MAX_DESCRIPTOR_LENGTH 256
#define MAX_LOCALITY_LENGTH 256
#define MAX_INDEX_ENTRIES 1000

typedef struct {
    char filename[MAX_FILENAME_LENGTH];
    char descriptor[MAX_DESCRIPTOR_LENGTH];
    char locality[MAX_LOCALITY_LENGTH];
} IndexEntry;

void indexImages(const char* imageDir, const char* descriptorDir, const char* indexFile) {
    DIR *dir;
    struct dirent *entry;
    IndexEntry indexEntries[MAX_INDEX_ENTRIES];
    int numEntries = 0;

    // Open the image directory
    dir = opendir(imageDir);
    if (dir == NULL) {
        printf("Failed to open image directory.\n");
        return;
    }

    // Read image files and extract descriptors
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {  // Check if it's a regular file
            char imagePath[MAX_FILENAME_LENGTH];
            snprintf(imagePath, sizeof(imagePath), "%s/%s", imageDir, entry->d_name);

            // Extract descriptor
            // Replace this with your histogram extraction code
            char descriptor[MAX_DESCRIPTOR_LENGTH];
            snprintf(descriptor, sizeof(descriptor), "histogram_descriptor_of_%s", entry->d_name);

            // Store index entry
            IndexEntry indexEntry;
            strncpy(indexEntry.filename, entry->d_name, sizeof(indexEntry.filename));
            strncpy(indexEntry.descriptor, descriptor, sizeof(indexEntry.descriptor));
            strncpy(indexEntry.locality, "locality_of_image", sizeof(indexEntry.locality));
            indexEntries[numEntries++] = indexEntry;
        }
    }

    closedir(dir);

    // Save descriptors and create index file
    FILE* indexFilePtr = fopen(indexFile, "w");
    if (indexFilePtr == NULL) {
        printf("Failed to create index file.\n");
        return;
    }

    for (int i = 0; i < numEntries; i++) {
        // Save descriptor file
        char descriptorFile[MAX_FILENAME_LENGTH];
        snprintf(descriptorFile, sizeof(descriptorFile), "%s/extractor_j/%s.txt", descriptorDir, indexEntries[i].filename);
        FILE* descriptorFilePtr = fopen(descriptorFile, "w");
        if (descriptorFilePtr == NULL) {
            printf("Failed to create descriptor file for %s.\n", indexEntries[i].filename);
            continue;
        }
        fprintf(descriptorFilePtr, "%s", indexEntries[i].descriptor);
        fclose(descriptorFilePtr);

        // Save index entry
        fprintf(indexFilePtr, "%s\t%s\t%s\n", indexEntries[i].filename, indexEntries[i].descriptor, indexEntries[i].locality);
    }

    fclose(indexFilePtr);

    printf("Indexing complete.\n");
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: ./index_images image_directory descriptor_directory index_file\n");
        return 0;
    }

    char* imageDir = argv[1];
    char* descriptorDir = argv[2];
    char* indexFile = argv[3];

    indexImages(imageDir, descriptorDir, indexFile);

    return 0;
}
