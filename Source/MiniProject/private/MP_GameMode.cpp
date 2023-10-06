// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_GameMode.h"
#include "MP_Player.h"
#include "MP_PlayerController.h"

AMP_GameMode::AMP_GameMode()
{
	DefaultPawnClass = AMP_Player::StaticClass();
	PlayerControllerClass = AMP_PlayerController::StaticClass();
}
