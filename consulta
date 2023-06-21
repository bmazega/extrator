#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_FILENAME_LENGTH 256
#define MAX_DESCRIPTOR_LENGTH 256
#define MAX_LOCALITY_LENGTH 256
#define MAX_QUERY_RESULTS 5

typedef struct {
    char descriptor[MAX_DESCRIPTOR_LENGTH];
    char locality[MAX_LOCALITY_LENGTH];
} DescriptorEntry;

typedef struct {
    char filename[MAX_FILENAME_LENGTH];
    double distance;
} QueryResult;

double calculateEuclideanDistance(const char* descriptor1, const char* descriptor2) {
    // Replace this with your implementation of Euclidean distance calculation
    // The function should compare the descriptors and return the distance
    // Here's a dummy implementation that returns a random distance value
    return rand() % 100;
}

void queryImages(const char* queryImage, const char* descriptorDir, const char* extractorType, int topK) {
    // Load descriptors associated with the specified extractor type into a linked list
    DescriptorEntry* descriptors = NULL;
    int numDescriptors = 0;

    char indexFile[MAX_FILENAME_LENGTH];
    snprintf(indexFile, sizeof(indexFile), "index_%s.txt", extractorType);
    FILE* indexFilePtr = fopen(indexFile, "r");
    if (indexFilePtr == NULL) {
        printf("Failed to open index file.\n");
        return;
    }

    char line[MAX_DESCRIPTOR_LENGTH + MAX_FILENAME_LENGTH + MAX_LOCALITY_LENGTH];
    while (fgets(line, sizeof(line), indexFilePtr) != NULL) {
        char* filename = strtok(line, "\t");
        char* descriptor = strtok(NULL, "\t");
        char* locality = strtok(NULL, "\n");

        DescriptorEntry descriptorEntry;
        strncpy(descriptorEntry.descriptor, descriptor, sizeof(descriptorEntry.descriptor));
        strncpy(descriptorEntry.locality, locality, sizeof(descriptorEntry.locality));

        numDescriptors++;
        descriptors = (DescriptorEntry*)realloc(descriptors, numDescriptors * sizeof(DescriptorEntry));
        descriptors[numDescriptors - 1] = descriptorEntry;
    }

    fclose(indexFilePtr);

    // Extract descriptor for the query image
    char queryDescriptor[MAX_DESCRIPTOR_LENGTH];
    // Replace this with your code to extract the descriptor for the query image
    strncpy(queryDescriptor, "descriptor_of_query_image", sizeof(queryDescriptor));

    // Calculate distances and find top-K similar images
    QueryResult queryResults[MAX_QUERY_RESULTS];
    for (int i = 0; i < numDescriptors; i++) {
        double distance = calculateEuclideanDistance(queryDescriptor, descriptors[i].descriptor);
        if (i < topK) {
            QueryResult queryResult;
            strncpy(queryResult.filename, descriptors[i].locality, sizeof(queryResult.filename));
            queryResult.distance = distance;
            queryResults[i] = queryResult;
        } else {
            int maxIndex = 0;
            double maxDistance = queryResults[0].distance;
            for (int j = 1; j < topK; j++) {
                if (queryResults[j].distance > maxDistance) {
                    maxIndex = j;
                    maxDistance = queryResults[j].distance;
                }
            }
            if (distance < maxDistance) {
                strncpy(queryResults[maxIndex].filename, descriptors[i].locality, sizeof(queryResults[maxIndex].filename));
                queryResults[maxIndex].distance = distance;
            }
        }
    }

       // Display top-K localities
    printf("Top-%d localities:\n", topK);
    for (int i = 0; i < topK; i++) {
        printf("%s\n", queryResults[i].filename);
    }

    // Free memory
    free(descriptors);
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Usage: ./query query_image descriptor_directory extractor_type top_k\n");
        return 0;
    }

    char* queryImage = argv[1];
    char* descriptorDir = argv[2];
    char* extractorType = argv[3];
    int topK = atoi(argv[4]);

    queryImages(queryImage, descriptorDir, extractorType, topK);

    return 0;
}

   
