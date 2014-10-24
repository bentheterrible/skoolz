#include <stdio.h>

int main() {

	int row, col;

	double times[12];
	int sets[12];
	int i;	

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


		// Calculate Times	
		best_time = times[0];		// Default the best time to first time
		worst_time = times[0];		// Default the worst time to first time

		// Calculate Sets 
		best_sets = sets[0];		// Default the best set to first set 
		worst_sets = sets[0];		// Default the worst set to first set 

		// As of now the best/worst times and sets are defaulted to the first
		// value of each one of the arrays
		//
		// This next loop runs through each one of the loops and tests to see
		// if any of the values beat the best/worst times or sets and UPDATE
		// the new best/worst time or set
		//
		// Inside it adds up all the values and when it exists the loop it
		// divides the sum total of times/sets by the number of times and 
		// sets to give you the average :3 

		// Find best/worst times
		for (i = 0; i < 12; i++) {
			
			// Check for best time
			if (times[i] > best_time) {
				best_time = time[i]
			}

			// Check for worst time
			if (times[i] < worst_time) {
				worst_time = time[i]
			}
			
			// Check for the best set	
			if (sets[i] > best_sets) {
				best_sets = sets[i];
			}

			// Check for the best set	
			if (sets[i] < worst_sets) {
				worst_sets = sets[i];
			}

			// Add up all the times	
			average_time += time[i];

			// Add up all the sets 
			average_sets += time[i];
		}	

		// Divide by number of times to get average time
		average_time /= 12.0;

		// Divide by number of sets to get average sets 
		average_sets /= 12;

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
