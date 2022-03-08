#include <stdio.h>
char readEngineTemp(double * engine_temp){
    double input;
    printf("Set The Engine Temp\n");
    scanf(" %lf",&input);
    if(input<100||input>150){
        *engine_temp=125;
        return 1;
    }else{
        *engine_temp=input;
        return 0;
    }
    return 0;
}
char readRoomTemp(double * room_temp){
    double input;
    printf("Set The Room Temp\n");
    scanf(" %lf",&input);
    if(input<10||input>30){
        *room_temp=20;
        return 1;
    }else{
        *room_temp=input;
        return 0;
    }
    return 0;
}
char readTraffic(){
    char input;
    do{
        printf("Set Traffic light color\n");
        scanf(" %c",&input);
    }while(input!='G'&&input!='R'&&input!='O');
    if(input=='G'){
        return 100;
    }else if(input=='O'){
        return 30;
    }else{
        return 0;
    }
    return 0;
}
void printState(int speed,int EngTempController,int AC,int EngineState,double room_temp,double engine_temp){
    printf("=============================================\n");
    if(EngineState) printf("i. Engine state: ON\n");
    else printf("i. Engine state: OFF\n");

    if(AC) printf("ii. AC: ON\n");
    else printf("ii. AC: OFF\n");

    printf("iii. Vehicle Speed: %d\n",speed);
    printf("iv. Room Temperature: %lf\n",room_temp);

    if(EngTempController) printf("v. Engine Temperature Controller State: ON\n");
    else printf("v. Engine Temperature Controller State: OFF\n");

    printf("iv. Engine Temperature: %lf\n",engine_temp);
    printf("=============================================\n");
}
int turnOn(){
    char input;
    int speed=0,EngTempController=0,AC=0,EngineState=0;
    double room_temp=25,engine_temp=125;
    speed=readTraffic();
    while(1){
        if(speed>0){
            EngineState=1;
        }
        if(speed==30){
           AC=1;
           room_temp = room_temp *0.8 + 1;

           EngTempController = 1;
          engine_temp = room_temp *0.8 + 1;
        }

        printState(speed,EngTempController,AC,EngineState,room_temp,engine_temp);

        do{
        printf("a. Turn off the engine\n");
        printf("b. Set the traffic light color\n");
        printf("c. Set the room temperature (Temperature Sensor)\n");
        printf("d. Set the engine temperature (Engine Temperature Sensor)\n");
        scanf(" %c",&input);
        }while(input!='a'&&input!='b'&&input!='c'&&input!='d');
        if(input=='a'){
            EngineState=0;
            return 1;
        }else if(input=='b'){
            speed=readTraffic();
        }else if(input=='c'){
            AC=readRoomTemp(&room_temp);
        }else{
            EngTempController=readEngineTemp(&engine_temp);
        }
    }

    return 0;
}
int mainDecide(){
    char input;
    do{
        printf("Welcome to the system:\n");
        printf("a. Turn on the vehicle engine\n");
        printf("b. Turn off the vehicle engine\n");
        printf("c. Quit the system\n");
        scanf(" %c",&input);
    }while(input!='a'&&input!='b'&&input!='c');
    if(input == 'a'){
        if(turnOn()) mainDecide();
        else return 0;
    }
    if(input == 'b'){
        printf("c. Are you sure?\n");
        scanf(" %c",&input);
        printf("vehicle engine turned off!\n");
        mainDecide();
    }
    if(input=='c')  return 0;
    return 0;
}


int main(){
    if(mainDecide()==0){
        return 0;
    }
    return 0;
}
