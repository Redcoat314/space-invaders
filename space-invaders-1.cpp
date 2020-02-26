#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<string.h>
#include<time.h>
void populate();
int theGame();
void print();
void pauseTheGame();
void update();
void invaderLaserProduction();
void playerControl();
void laserUpdate();
int i = 0;
int j = 0;
int yAxis = 25;
int xAxis = 40;
int totalInvaders = 0;
int shieldFlag = 1;
int F = 0, score = 0, it = 1, n = 16, victory = 1, laserReady = 0, activeInvaderFlag = 0,activeInvaderCoordinateX,activeInvaderCoordinateY;
char world[25][40];
char invader = 'W', player = 'A', shield = 'O', playerLaser='!', direction = 'r', invaderLaser = 'T';
int main(){
	int vic = 0, bonus = 0;
	printf("\n\n\n\tControls:\n\t\'a\' to move left\n\t\'d\' to move right\n\t\'m\' to shoot\n\t\'p' to pause the game\n\n");
	printf("\n\tEpilepsy Warning: Blinking Lights\n");
	printf("\n\tPress any key to continue...");
	getch();
	populate();
	vic = theGame();
	print();
	Sleep(500);
}
void pauseTheGame(){
	char y;
	y = getch();
}
void populate(){
		for( i = 0; i < yAxis; i++){		
			for (j = 0; j < xAxis; j++){				
				if ((j > 3 && j < xAxis - 4) && j % 2 == 0 && i % 2 == 0 && i < yAxis / 3){					
					world[i][j] = invader;				
					totalInvaders++;					
				}				
				else if(i == 21 && (j == shieldFlag || j == shieldFlag + 1 || j == shieldFlag + 2)){				
					world[i][j] = shield;						
					F=1;					
				}
				else{				
					world[i][j] = ' ';					
					if(F){					
						shieldFlag += 5;						
						F = 0;				
					}
				}
			}	
		}
		world[yAxis-1][xAxis/2] = 'A';
}
void invaderLaserProduction(){
	int laserFrequency = (rand() % 10) > 8;
	boolean laserClearance = world[j][i] == invader && world[j + 2][i] != invader && world[j + 4][i] != invader;
	if(laserFrequency && laserClearance){
		world[j + 1][i] = invaderLaser;
	}
}
void playerControl(){
	char keyPress;
	if(kbhit()){
           keyPress = getch();        	
    }        
	else{
        keyPress = ' ';            
    }
	if (keyPress == 'a') {        
		for(i = 0; i < xAxis; i++){            
			if(world[yAxis - 1][i + 1] == player){
				world[yAxis - 1][i] = player;                    
            	world[yAxis - 1][i + 1] = ' ';                    
            }
        }
    }
    if(keyPress == 'd'){
	    for (i = xAxis - 1; i > 0; i--){
    	    if( world[yAxis - 1][i - 1] == player){
                world[yAxis - 1][i] = player;                   
                world[yAxis - 1][i - 1] = ' ';
            }
        }
    }
    if(keyPress == 'm' && laserReady > 1){
        for(i = 0; i < xAxis; i++){            
            if(world[yAxis - 1][i] == player){
                world[yAxis - 2][i] = playerLaser;                    
                laserReady = 0;
            }
        }
    }
    if(keyPress == 'p'){
        pauseTheGame();
    }
    laserReady++;
}
void print(){
	int r = 0, c = 0;
	system("cls");
	printf("\tSCORE: %4d \n", score);		
	for(r = 0; r < yAxis; r++){
		printf("|");
		for (c = 0; c < xAxis; c++){						
			printf("%c", world[r][c]);				
		}				
		printf("|\n");				
	}
}
void laserUpdate(){
	char explosion = 'X';
	//laser control
	for(i = 0; i < xAxis; i++){
		for(j = yAxis - 1; j >= 0; j--){
			if((j == 0 || j == yAxis - 1) && (world[j][i] == 'T' || world[j][i] == '!'))
				world[j][i] = ' ';
			else if(world[j][i] == invaderLaser){
				if(world[j + 1][i] == shield){
					world[j + 1][i] = ' ';						
					world[j][i] = ' ';						
				}
				else if(world[j + 1][i] == player){
					world[j + 1][i] = explosion;											
					victory = 0;						
					break;							
				}
				else if(world[j + 1][i] == playerLaser){				
					world[j][i] = explosion;			
					world[j + 1][i] = ' ';
				}
				else{
					world[j + 1][i] = invaderLaser;						
					world[j][i] = ' ';					
				}
			}
			else if(world[j][i] == playerLaser){						
				if(world[j - 1][i] == invaderLaser){							
					world[j - 1][i] = explosion;							
					world[j][i] = ' ';												
				}									
				else if(world[j - 1][i] == invader){					
					world[j - 1][i] = explosion;						
					world[j][i] = ' ';						
					score += 50;						
					totalInvaders--;												
					if(totalInvaders == 0){							
						victory = 0;							
						break;			
					}									
				}
				else if(world[j - 1][i] == shield){						
					world[j][i] = ' ';						
				}					
				else{						
					world[j][i] = ' ';
					world[j - 1][i] = playerLaser;
					j--;
				}
			}
			else if(world[j][i] == explosion){
				print();
				Sleep(50);
				world[j][i] = ' ';
			}
			invaderLaserProduction();
		}
	}
}
void update(){
	int t = 0, k, l;
	//Invader Movement Control
	if(it > n){		
		for(i = 0; i < yAxis; i++){
			t=0;
			if(direction == 'r'){
				for(j = 0; j < xAxis; j++){
					if(world[i][j] == invader && world[i][xAxis-1] != invader){
						world[i][j + 1] = world[i][j];
						world[i][j] = ' ';
						j++;
					}
					else if(world[i][xAxis - 1] == invader){					
						for(k = 0; k < yAxis; k++){
							for(l = xAxis - 1; l >= 0; l--){
								if(world[k][l] == invader){
									world[k + 1][l] = world[k][l];
									world[k][l] = ' ';									
									l--;									
									t = 1;
								}
							}
							if(t == 1)
								k++;
						}
						n--;
						direction = 'l';
					}
				}
			}
			//moving left
			else{			
				for(j = xAxis - 1; j >= 0; j--){				
					if(world[i][j] == invader && world[i][0] != invader){					
						world[i][j - 1] = world[i][j];						
						world[i][j] = ' ';						
						j--;					
					}					
					else if(world[i][0] == invader){					
						for(k = 0; k < yAxis; k++){					
							for(l = 0; l < xAxis; l++){						
								if(world[k][l] == invader){								
									world[k + 1][l] = world[k][l];								
									world[k][l] = ' ';									
									l++;									
									t=1;
								}
							}
							if(t==1)
								k++;								
						}						
						n--;
						direction = 'r';
					}
				}				
			}
			//area invaders need to conquer to win
			if(world[19][0] == invader){			
				victory = 0;				
				print();
				break;								
			}
		}
	}
	if(it > n){		
		it = 1;
	}
	else{		
		it++;
	}
	laserUpdate();
	//player movement
	playerControl();
}
int theGame(){
	srand(time(0));
	while(victory){	
		update();			
		print();	
		Sleep(100);
	}
	return victory;
}
