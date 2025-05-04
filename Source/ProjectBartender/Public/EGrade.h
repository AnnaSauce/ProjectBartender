#pragma once

#include "CoreMinimal.h"
#include "EGrade.generated.h"

UENUM(BlueprintType)
enum class EGrade : uint8
{
	S UMETA(DisplayName = "S-Class"),
	A UMETA(DisplayName = "A-Class"),
	B UMETA(DisplayName = "B-Class"),
	C UMETA(DisplayName = "C-Class"),
	F UMETA(DisplayName = "F-Class"),
};