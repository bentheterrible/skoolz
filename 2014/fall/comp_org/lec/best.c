/* Gia Fiocco
 *10.23.14
 *COP 3223
 */

//libraries
#include <stdio.h>

//main function
int main(){
    FILE *ifp;
    ifp = fopen("input.txt", "r");
    double times[12];
    int sets[12];
    double best_time, worst_time, average_time, average_sets, worst_sets, most_sets;
    int i, row, col; 
    
    for (row = 0; row < 10; row++) {
        for (col = 0; col < 12; col++) {
            fscanf(ifp,"%lf",&times[col]);
        }
        for (col = 0; col < 12; col++) {
            fscanf(ifp,"%d",&sets[col]);
        }
      	
        best_time = times[0];
        worst_time = times[0];
    
        most_sets = sets[0];
        worst_sets = sets[0];

   		average_time = 0;
		average_sets = 0;

        for(i=0; i < 12; i++) {
        
            if(times[i] < best_time) {
                best_time = times[i];
            }
            if(times[i] > worst_time) {
                worst_time = times[i];
            }
            if(sets[i] > most_sets){
                most_sets = sets[i];
            }
            if(sets[i] < worst_sets){
                worst_sets = sets[i];
            }
        
            average_time += times[i];
            average_sets += sets[i];
            
        }
        average_time = average_time/12;
        average_sets = average_sets/12;

        //output
        printf("Participant #%d\n", row+1);
        printf("Cardio workout: \n");
        printf("\tBest time: %.2lf\n", best_time);
        printf("\tWorst Time: %.2lf\n", worst_time);
        printf("\tAverage time: %.2lf\n", average_time);
        
		printf("Weight workouts: \n");
        printf("\tMost sets: %.0lf\n", most_sets);
        printf("\tWorst sets: %.0lf\n", worst_sets);
        printf("\tAverage sets: %.2lf\n", average_sets);
        printf("\n");
        
    } // end big for loop
    
    return 0;
}
