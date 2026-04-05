#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100

// FUCNTION  TO ENSURE THE VALIDATION OF DNA SEQUENCE
// it makes sure the sequence contains only valid nucleotides: A, T, C, G
int validSequence(char sequence[]) {
  for (int i = 0; sequence[i] != '\0'; i++) {
    char c = toupper(sequence[i]);
    if (c != 'A' && c != 'C' && c != 'T' && c != 'G')
      return 0; // For Invalid character 
  }
  return 1; // if sequence is valid
}

// Function to calculate nucleotide composition
// Calculates the percentage of each nucleotide (A, T, C, G) in the sequence
void composition(char sequence[]) {
  int length = strlen(sequence);
  int a = 0, t = 0, g = 0, c = 0;
  for (int i = 0; i < length; i++) {
    char ch = toupper(sequence[i]);
    if (ch == 'A') a++;
    else if (ch == 'C') c++;
    else if (ch == 'T') t++;
    else if (ch == 'G') g++;
  }
  // Print the composition percentages
  printf("NUCLEOTIDE COMPOSITION:\n");
  printf("A: %.2f%%\n", (double)(a * 100) / length);
  printf("C: %.2f%%\n", (double)(c * 100) / length);
  printf("T: %.2f%%\n", (double)(t * 100) / length);
  printf("G: %.2f%%\n", (double)(g * 100) / length);
}

// Function to calculate GC content
// Calculates the percentage of G and C nucleotides in the sequence
void GCcontent(char sequence[]) {
  int length = strlen(sequence);
  int GCcount = 0;

  for (int i = 0; i < length; i++) {
    char ch = toupper(sequence[i]);
    if (ch == 'C' || ch == 'G')
      GCcount++;
  }

  // Printing the GC content percentage
  printf("GC CONTENT: %.2f%%\n", (double)(GCcount * 100) / length);
}

// Function to transcribe DNA to mRNA
// Converts DNA sequence to its corresponding mRNA sequence
void transcribeToMRNA(char sequence[]) {
  char mRNA[MAX_LEN + 1];
  int length = strlen(sequence);

  for (int i = 0; i < length; i++) {
    char ch = toupper(sequence[i]);
    switch (ch) {
      case 'A': mRNA[i] = 'U'; break; // A to  U
      case 'T': mRNA[i] = 'A'; break; // T to A
      case 'C': mRNA[i] = 'G'; break; // C to  G
      case 'G': mRNA[i] = 'C'; break; // G to C
    }
  }
  mRNA[length] = '\0'; // Null charahter to mark the end of  the mRNA string

  // Print the transcribed mRNA sequence
  printf("mRNA transcription: %s\n", mRNA);
}

// Function to translate mRNA to amino acids
// Converts mRNA sequence into amino acids based on codons
void translateToAminoAcids(char sequence[]) {
  int length = strlen(sequence);

  // Ensure the sequence length is a multiple of 3
  if (length % 3 != 0) {
    printf("Invalid sequence: Length must be a multiple of 3.\n");
    return;
  }

  printf("\nTranslation:\n");
  for (int i = 0; i < length; i += 3) {
    char codon[4];
    strncpy(codon, sequence + i, 3); // Extract a codon (3 nucleotides)
    codon[3] = '\0'; // Null-terminate the codon

    // Determine the corresponding amino acid for the codon
    const char *aminoAcid = "Unknown";
    if (strcmp(codon, "AUG") == 0) aminoAcid = "Methionine";
    else if (strcmp(codon, "UUU") == 0 || strcmp(codon, "UUC") == 0) aminoAcid = "Phenylalanine";
    else if (strcmp(codon, "UUA") == 0 || strcmp(codon, "UUG") == 0 || strcmp(codon, "CUU") == 0 ||
         strcmp(codon, "CUC") == 0 || strcmp(codon, "CUA") == 0 || strcmp(codon, "CUG") == 0) aminoAcid = "Leucine";
    else if (strcmp(codon, "AUU") == 0 || strcmp(codon, "AUC") == 0 || strcmp(codon, "AUA") == 0) aminoAcid = "Isoleucine";
    else if (strcmp(codon, "GUU") == 0 || strcmp(codon, "GUC") == 0 || strcmp(codon, "GUA") == 0 || strcmp(codon, "GUG") == 0) aminoAcid = "Valine";
    else if (strcmp(codon, "UCU") == 0 || strcmp(codon, "UCC") == 0 || strcmp(codon, "UCA") == 0 || strcmp(codon, "UCG") == 0) aminoAcid = "Serine";
    else if (strcmp(codon, "CCU") == 0 || strcmp(codon, "CCC") == 0 || strcmp(codon, "CCA") == 0 || strcmp(codon, "CCG") == 0) aminoAcid = "Proline";
    else if (strcmp(codon, "ACU") == 0 || strcmp(codon, "ACC") == 0 || strcmp(codon, "ACA") == 0 || strcmp(codon, "ACG") == 0) aminoAcid = "Threonine";
    else if (strcmp(codon, "GCU") == 0 || strcmp(codon, "GCC") == 0 || strcmp(codon, "GCA") == 0 || strcmp(codon, "GCG") == 0) aminoAcid = "Alanine";
    else if (strcmp(codon, "UAA") == 0 || strcmp(codon, "UAG") == 0 || strcmp(codon, "UGA") == 0) aminoAcid = "STOP";

    // Stop translation if a stop codon is encountered
    if (strcmp(aminoAcid, "STOP") == 0) {
      printf("Stop codon encountered at %s. Translation ends.\n", codon);
      break;
    }

    // Print the codon and its corresponding amino acid
    printf("%s -> %s\n", codon, aminoAcid);
  }
}

int main() {
  char dnaSequence[MAX_LEN + 1]; // Buffer to store the DNA sequence
  int choice;

  do {
    // Main menu
    printf("\n--- DNA Sequence Analyzer ---\n");
    printf("1. Enter DNA Sequence\n");
    printf("2. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // Consume newline character left by scanf

    if (choice == 1) {
      // Input DNA sequence
      printf("Enter DNA sequence (max 100 characters): ");
      fgets(dnaSequence, sizeof(dnaSequence), stdin);
      dnaSequence[strcspn(dnaSequence, "\n")] = '\0'; // Remove newline

      // Validate the DNA sequence
      if (!validSequence(dnaSequence)) {
        printf("Invalid DNA sequence! Only A, T, C, G are allowed.\n");
        continue;
      }

      int outputChoice;
      do {
        // Analysis options menu
        printf("\n--- Analysis Options ---\n");
        printf("1. DNA Composition\n");
        printf("2. GC Content\n");
        printf("3. Transcribe to mRNA\n");
        printf("4. Translate to Amino Acids\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &outputChoice);
        getchar(); // Consume newline

        char mRNA[MAX_LEN + 1]; // Buffer for mRNA sequence

        switch (outputChoice) {
          case 1:
            // Calculate and display DNA composition
            composition(dnaSequence);
            break;
          case 2:
            // Calculate and display GC content
            GCcontent(dnaSequence);
            break;
          case 3:
            // TO TRANSCRIBE DNA to mRNA
            strcpy(mRNA, dnaSequence);
            transcribeToMRNA(mRNA);
            printf("Transcribed mRNA: %s\n", mRNA);
            break;
          case 4:
            // transcribe DNA to mRNA and translate to amino acids
            strcpy(mRNA, dnaSequence);
            transcribeToMRNA(mRNA);
            translateToAminoAcids(mRNA);
            break;
          case 5:
            // return to main menu
            printf("Returning to main menu...\n");
            break;
          default:
            // Handle invalid input
            printf("Invalid choice! Try again.\n");
        }

      } while (outputChoice != 5); // To repeat until user chooses to return to main menu
    }

  } while (choice != 2); // to Repeat until user chooses to exit

  printf("Program exited.\n");
  return 0;
}