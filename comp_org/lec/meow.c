#include <stdio.h>

int main() {

	int row, col;

	double times[12];
	int sets[12];
	
	double best_time, worst_time, average_time;
	int most_sets, least_sets, average_sets;

	int winner;		// Participant 1

	for(row = 0; row < 10; row++) {

		// Populates time array
		for(col = 0; col < 12; col++) {
			fscanf(ifp, "%.1lf", times[col]);
		}

		// Populates set array
		for(col = 0; col < 12; col++) {
			fscanf(ifp, "%d", sets[col]);
		}

	
		// Figure out the logic for everything
		

		// Output
		printf("Participant #%d\n", row+1);
		printf("Cardio Workouts: \n");
		printf("\tBest Time: %.1lf\n", best_time);
		printf("\tWorst Time: %.1lf\n", worst_time);
		printf("\tAverage Time: %.1lf\n", average_time);
		printf("Weight Workouts:\n");
		printf("\tMost Sets: %d\n", most_sets);
		printf("\tLeast Sets: %d\n", least_sets);
		printf("\tAverage Sets: %d\n", average_sets);
		printf("\n");
	}	
}
