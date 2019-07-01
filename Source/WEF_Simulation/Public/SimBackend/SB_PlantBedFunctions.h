#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SB_PlantBedFunctions.generated.h"

/**
 * Author: Garrett Fairburn
 * Created: 2019-07-01
 * Modified: 2019-07-01
 *
 * This class provides static, blueprint-callable functions to assist the SB_PlantBed actor component class.
 */
UCLASS()
class WEF_SIMULATION_API USB_PlantBedFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "SB_PlantBedFunctions")
	static void getGrowthAmount(
		// Input parameters.
		const float deltaTime,
		const float liquidConsumptionCoeff,
		const float plantGrowthCoeff,
		const float liquidAvailable,
		const float currentPlantHeight,
		const float maxPlantHeight,
		// Output parameters.
		float& liquidConsumed,
		float& plantGrowthAmount
	);
};
