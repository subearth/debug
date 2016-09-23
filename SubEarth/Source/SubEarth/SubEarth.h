// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
//#include "EngineMinimal.h"

/* Using UE_LOG
UE_LOG's write real time to an output window and to a file after the application ends.

Quick reference on how to use

UE_LOG(LogTemp, Log, TEXT("This is grey text!"));
UE_LOG(LogTemp, Warning, TEXT("This is yellow text!"));
UE_LOG(LogTemp, Error, TEXT("This is red text!"));
UE_LOG(LogTemp, Fatal, TEXT("This will cause your system to crash"));

You can also add common separated arguments!
UE_LOG(LogTemp, Warning, TEXT("FIRE Count: %d %f"), some_int, some_float);

Accessing your logs

To see logs real time
(UE4) Window -> Developer Tools -> Output Log

Everything is saved to a file. (file updates after program stops)
SubEarth\Saved\Logs\SubEarth.log    (Search for LogTemp)

On screen debug messages

GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Some variable values: x: %f, y: %f"), x, y));

References
https://wiki.unrealengine.com/Logs,_Printing_Messages_To_Yourself_During_Runtime
*/