// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(MiniProject, Log, All);
#define ABLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define ABLOG_S(Verbosity) UE_LOG(MiniProject, Verbosity, TEXT("%s"), *ABLOG_CALLINFO)
#define ABLOG(Verbosity, Format, ...) UE_LOG(MiniProject, Verbosity, TEXT("%s %s"), *ABLOG_CALLINFO, *FString::Prinrf(Format, ##__VA_ARGS__))
#define ABCHECK(Expr, ...) { if(!(Expr)) {ABLOG(Error, "ASSERTION : %s", TEXT("'"#Expr"'")); return __VA_ARGS__; } }
