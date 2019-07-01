#include "SB_PlantBedFunctions.h"


void USB_PlantBedFunctions::getGrowthAmount(
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
) {
	// Ensure there is available liquid and growth height.
	if (liquidAvailable > 0.0 && currentPlantHeight < maxPlantHeight) {
		// Calculate coefficient ratio.
		float liquidPerPlant = liquidConsumptionCoeff / plantGrowthCoeff;

		// Calculate prospective output parameters.
		liquidConsumed = deltaTime * liquidConsumptionCoeff;
		plantGrowthAmount = deltaTime * plantGrowthCoeff;

		// Check if there is enough available liquid.
		if (liquidConsumed > liquidAvailable) {
			// Reduce amounts accordingly.
			liquidConsumed = liquidAvailable;
			plantGrowthAmount = liquidConsumed / liquidPerPlant;
		}

		// Check if there is enough available height.
		if (currentPlantHeight + plantGrowthAmount > maxPlantHeight) {
			// Reduce amounts accordingly.
			plantGrowthAmount = maxPlantHeight - currentPlantHeight;
			liquidConsumed = plantGrowthAmount * liquidPerPlant;
		}
	}
	else {
		liquidConsumed = 0.0;
		plantGrowthAmount = 0.0;
	}

	return;
}