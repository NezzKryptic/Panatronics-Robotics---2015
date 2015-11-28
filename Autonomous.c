#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S3,     gyroSensor,     sensorI2CHiTechnicGyro)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     blWheel,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     brWheel,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     frWheel,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     spinMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     flWheel,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    launch,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    frontServo,           tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C2_3,    backServo,            tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Pre-Made Class With Joystick Vars
#include "JoystickDriver.c"

// Set Motor Speeds
void setMotors(int backLeftWheel, int backRightWheel, int frontLeftWheel, int frontRightWheel)
{
	// Front Motors
	motor[flWheel] = frontLeftWheel;
	motor[frWheel] = frontRightWheel;

	// Back Motors
	motor[blWheel] = backLeftWheel;
	motor[brWheel] = backRightWheel;
}

// Set Spinner Speed
void setSpinner(int spinSpeed)
{
	motor[spinMotor] = spinSpeed;
}

// Set Robot Angle
void setAngle(int degreesToTurn, int motorSpeed)
{
	float degreesSoFar = 0;
	int initialTurnReading = SensorValue[gyroSensor];

	setMotors(-motorSpeed * sgn(degreesToTurn), -motorSpeed * sgn(degreesToTurn), -motorSpeed * sgn(degreesToTurn), -motorSpeed * sgn(degreesToTurn));

	while(abs(degreesSoFar) < abs(degreesToTurn))
	{
		wait1Msec(10);
		int currentGyroReading = SensorValue(gyroSensor) - initialTurnReading;
		degreesSoFar = degreesSoFar + currentGyroReading * 0.01;
	}

	setMotors(0, 0, 0, 0);
}

// Function To Simplify Auton Movement
void loadDirections(int *directionCommands, int arraySize)
{
	// Current Command Index
	int currentIndex = 0;

	// Loop Through Commands And Act Accordingly
	while(currentIndex < arraySize)
	{
		if(directionCommands[currentIndex] == 0)
		{
			// Stop
			setMotors(0, 0, 0, 0);
			wait1Msec(directionCommands[currentIndex + 1]);
			currentIndex += 2 ;
		}
		else if(directionCommands[currentIndex] == 1)
		{
			// Forward
			setMotors(-directionCommands[currentIndex + 2], directionCommands[currentIndex + 2], -directionCommands[currentIndex + 2], directionCommands[currentIndex + 2]);
			wait1Msec(directionCommands[currentIndex + 1]);
			currentIndex += 3;
		}
		else if(directionCommands[currentIndex] == 2)
		{
			// Backward
			setMotors(directionCommands[currentIndex + 2], -directionCommands[currentIndex + 2], directionCommands[currentIndex + 2], -directionCommands[currentIndex + 2]);
			wait1Msec(directionCommands[currentIndex + 1]);
			currentIndex += 3;
		}
		else if(directionCommands[currentIndex] == 3)
		{
			// Strafe Left
			setMotors(-directionCommands[currentIndex + 2], -directionCommands[currentIndex + 2], directionCommands[currentIndex + 2], directionCommands[currentIndex + 2]);
			wait1Msec(directionCommands[currentIndex + 1]);
			currentIndex += 3;
		}
		else if(directionCommands[currentIndex] == 4)
		{
			// Strafe Right
			setMotors(directionCommands[currentIndex + 2], directionCommands[currentIndex + 2], -directionCommands[currentIndex + 2], -directionCommands[currentIndex + 2]);
			wait1Msec(directionCommands[currentIndex + 1]);
			currentIndex += 3;
		}
		else if(directionCommands[currentIndex] == 5)
		{
			// Rotate Left
			setMotors(directionCommands[currentIndex + 2], directionCommands[currentIndex + 2], directionCommands[currentIndex + 2], directionCommands[currentIndex + 2]);
			wait1Msec(directionCommands[currentIndex + 1]);
			currentIndex += 3;
		}
		else if(directionCommands[currentIndex] == 6)
		{
			// Rotate Right
			setMotors(-directionCommands[currentIndex + 2], -directionCommands[currentIndex + 2], -directionCommands[currentIndex + 2], -directionCommands[currentIndex + 2]);
			wait1Msec(directionCommands[currentIndex + 1]);
			currentIndex += 3;
		}
		else if(directionCommands[currentIndex] == 7)
		{
			// Spinner On
			setSpinner(directionCommands[currentIndex + 2]);
			wait1Msec(directionCommands[currentIndex + 1]);
			currentIndex += 3;
		}
		else if(directionCommands[currentIndex] == 8)
		{
			// Spinnner Off
			setSpinner(0);
			wait1Msec(directionCommands[currentIndex + 1]);
			currentIndex += 2;
		}
		else if(directionCommands[currentIndex] == 9)
		{
			// Set Angle
			setAngle(directionCommands[currentIndex + 3], directionCommands[currentIndex + 2]);
			wait1Msec(directionCommands[currentIndex + 1]);
			currentIndex += 4;
		}
		else if(directionCommands[currentIndex] == 10)
		{
			// FR Diagonal
			setMotors(0, directionCommands[currentIndex + 2], -directionCommands[currentIndex + 2], 0);
			wait1Msec(directionCommands[currentIndex + 1]);
			currentIndex += 3;
		}
		else if(directionCommands[currentIndex] == 11)
		{
			// BL Diagonal
			setMotors(0, -directionCommands[currentIndex + 2], directionCommands[currentIndex + 2], 0);
			wait1Msec(directionCommands[currentIndex + 1]);
			currentIndex += 3;
		}
		else if(directionCommands[currentIndex] == 12)
		{
			// FL Diagonal
			setMotors(-directionCommands[currentIndex + 2], 0, 0,directionCommands[currentIndex + 2]);
			wait1Msec(directionCommands[currentIndex + 1]);
			currentIndex += 3;
		}
		else if(directionCommands[currentIndex] == 13)
		{
			// BR Diagonal
			setMotors(directionCommands[currentIndex + 2], 0, 0, -directionCommands[currentIndex + 2]);
			wait1Msec(directionCommands[currentIndex + 1]);
			currentIndex += 3;
		}
	}
}

// Function To Initialize Robot
void initializeRobot()
{
	return;
}

// ######################################################################################//
// ## Numbers And Their Movement Equivalents
// ## 0 = Stop
// ## 1 = Forward 		| 2 = Backward
// ## 3 = StrafeLeft	| 4 = StrafeRight
// ## 5 = RotateLeft	| 6 = RotateRight
// ## 7 = Spinner On 	| 8 = Spinner Off
// ## 9 = Set Angle		| 10 = Locate IR
// ######################################################################################//

// Main Task To Run Robot
task main()
{
	// Call Initialize Function
	initializeRobot();

	// Wait For Computer To Tell Autonomous To Start
	waitForStart();

	// Command, Duration, Speed, ~Angle
	int commands[] = {
		0, 100
	};

	// Send commands to LoadDirections
	loadDirections(commands, sizeof(commands)/sizeof(commands[0]));
}
