#include "SB_PlantBedFunctions.h"


/**
* Assuming parameters from an SB_PlantBed and SB_LiquidContainer component that belong to the same actor,
* calculate how much liquid to consume from the SB_LiquidContainer and how many feet the plants should grow
* in the SB_PlantBed for a given frame.
*
* This functionality was implemented as a static C++ function rather than a blueprint method of SB_PlantBed
* because the calculation involves nested if statments that would be unnecessarily difficult to implement
* using blueprints.
*
* INPUTS:
*  deltaTime: the time (in seconds) that has elapsed since the previous frame
*  liquidConsumptionCoeff: the amount of liquid (in gallons) to consume per second
*  plantGrowthCoeff: the height (in feet) that the plants should grow per second
*  liquidAvailable: the amount of liquid (in gallons) that the SB_LiquidContainer has
*  currentPlantHeight: the current height (in feet) of the SB_PlantBed's plants
*  maxPlantHeight: the maximum allowable height (in feet) of the SB_PlantBed's plants
*
* OUTPUTS:
*  liquidConsumed: the amount of liquid (in gallons) to consume for this frame
*  plantGrowthAmount: the height (in feet) that the plants should grow for this frame
*/
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
		// Calculate coefficient ratio (i.e. liquid gallons required per foot of plant growth).
		float liquidPerPlant = liquidConsumptionCoeff / plantGrowthCoeff;

		// Calculate prospective output parameters.
		liquidConsumed = deltaTime * liquidConsumptionCoeff;
		plantGrowthAmount = deltaTime * plantGrowthCoeff;

		// Check if there is enough available liquid.
		if (liquidConsumed > liquidAvailable) {
			// Reduce the liquid consumption.
			liquidConsumed = liquidAvailable;
			// Since the liquid consumption was reduced, the plant growth must also be
			// reduced using the appropriate ratio.
			plantGrowthAmount = liquidConsumed / liquidPerPlant;
		}

		// Check if there is enough available height.
		if (currentPlantHeight + plantGrowthAmount > maxPlantHeight) {
			// Reduce the plant growth.
			plantGrowthAmount = maxPlantHeight - currentPlantHeight;
			// Since plant growth was reduced, the liquid consumed must also be reduced
			// using the appropriate ratio.
			liquidConsumed = plantGrowthAmount * liquidPerPlant;
		}
	} else {
		// If there is either no more liquid to consume or no more height to grow,
		// do not consume any liquid and do not grow the plants at all.
		liquidConsumed = 0.0;
		plantGrowthAmount = 0.0;
	}

	return;
}