/******************** MODULE.C **************************/
/*
 * Rory Barnes, Mon Jan 19 13:00:54 PST 2015
 *
 * Functions to manipulate the MODULE struct.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vplanet.h"

/* NULL functions for all module function pointer matrices. All pointers are
   initialized to point to these functions. Modules that require them reset
   the pointers in AddModuleX. */

void  InitializeControlNULL(CONTROL *control,int iBody) {
  // Nothing
}

void InitializeBodyNULL(BODY *body,CONTROL *control,UPDATE *update,int iBody,int iModule) {
}

void InitializeModuleNULL(CONTROL *control,MODULE *module) {
}

void InitializeUpdateTmpBodyNULL(BODY *body,CONTROL *control,UPDATE *update,int iBody) {
}

void FinalizeUpdateNULL(BODY *body,UPDATE *update,int *iEqn,int iVar,int iBody,int iFoo) {
  /* Nothing */
}

void PropsAuxNULL(BODY *body,EVOLVE *evolve,UPDATE *update,int iFoo) {
}

// Functions that are helpful for integrations

double fdReturnOutputZero(BODY *body,SYSTEM *system,UPDATE *update,int iBody,int iBody1) {
  return 0;
}

double fdUpdateFunctionTiny(BODY *body,SYSTEM *system,int *iaBody) {
  return TINY;
}

// Reset function pointer to return TINY
void SetDerivTiny(fnUpdateVariable ***fnUpdate,int iBody,int iVar,int iEqn) {
  fnUpdate[iBody][iVar][iEqn] = &fdUpdateFunctionTiny;
}

void InitializeModule(MODULE *module,int iNumBodies) {
  int iBody;

  module->iNumModules = malloc(iNumBodies*sizeof(int));
  module->iaModule = malloc(iNumBodies*sizeof(int*));
  module->iBitSum = malloc(iNumBodies*sizeof(int*));

  // Allow parameters that require no module
  for (iBody=0;iBody<iNumBodies;iBody++)
    module->iBitSum[iBody] = 1;

  // Function pointer vectors
  module->fnInitializeUpdate = malloc(iNumBodies*sizeof(fnInitializeUpdateModule));
  module->fnInitializeOutput = malloc(iNumBodies*sizeof(fnInitializeOutputModule*));

  // Finalize Primary Variable Functions
  //module->fnFinalizeUpdateEcc = malloc(iNumBodies*sizeof(fnFinalizeUpdateEccModule));
  module->fnFinalizeUpdate26AlNumCore = malloc(iNumBodies*sizeof(fnFinalizeUpdate26AlNumCoreModule));
  module->fnFinalizeUpdate26AlNumMan = malloc(iNumBodies*sizeof(fnFinalizeUpdate26AlNumManModule));
  module->fnFinalizeUpdate40KNumCore = malloc(iNumBodies*sizeof(fnFinalizeUpdate40KNumCoreModule));
  module->fnFinalizeUpdate40KNumCrust = malloc(iNumBodies*sizeof(fnFinalizeUpdate40KNumCrustModule));
  module->fnFinalizeUpdate40KNumMan = malloc(iNumBodies*sizeof(fnFinalizeUpdate40KNumManModule));
  module->fnFinalizeUpdate232ThNumCore = malloc(iNumBodies*sizeof(fnFinalizeUpdate232ThNumCoreModule));
  module->fnFinalizeUpdate232ThNumCrust = malloc(iNumBodies*sizeof(fnFinalizeUpdate232ThNumCrustModule));
  module->fnFinalizeUpdate232ThNumMan = malloc(iNumBodies*sizeof(fnFinalizeUpdate232ThNumManModule));
  module->fnFinalizeUpdate235UNumCore = malloc(iNumBodies*sizeof(fnFinalizeUpdate235UNumCoreModule));
  module->fnFinalizeUpdate235UNumCrust = malloc(iNumBodies*sizeof(fnFinalizeUpdate235UNumCrustModule));
  module->fnFinalizeUpdate235UNumMan = malloc(iNumBodies*sizeof(fnFinalizeUpdate235UNumManModule));
  module->fnFinalizeUpdate238UNumCore = malloc(iNumBodies*sizeof(fnFinalizeUpdate238UNumCoreModule));
  module->fnFinalizeUpdate238UNumCrust = malloc(iNumBodies*sizeof(fnFinalizeUpdate238UNumCrustModule));
  module->fnFinalizeUpdate238UNumMan = malloc(iNumBodies*sizeof(fnFinalizeUpdate238UNumManModule));

  module->fnFinalizeUpdateCBPR = malloc(iNumBodies*sizeof(fnFinalizeUpdateCBPRModule));
  module->fnFinalizeUpdateCBPZ = malloc(iNumBodies*sizeof(fnFinalizeUpdateCBPZModule));
  module->fnFinalizeUpdateCBPPhi = malloc(iNumBodies*sizeof(fnFinalizeUpdateCBPPhiModule));
  module->fnFinalizeUpdateCBPRDot = malloc(iNumBodies*sizeof(fnFinalizeUpdateCBPRDotModule));
  module->fnFinalizeUpdateCBPZDot = malloc(iNumBodies*sizeof(fnFinalizeUpdateCBPZDotModule));
  module->fnFinalizeUpdateCBPPhiDot = malloc(iNumBodies*sizeof(fnFinalizeUpdateCBPPhiDotModule));

  module->fnFinalizeUpdateDynEllip = malloc(iNumBodies*sizeof(fnFinalizeUpdateDynEllipModule));
  module->fnFinalizeUpdateEnvelopeMass = malloc(iNumBodies*sizeof(fnFinalizeUpdateEnvelopeMassModule));
  module->fnFinalizeUpdateHecc = malloc(iNumBodies*sizeof(fnFinalizeUpdateHeccModule));
  module->fnFinalizeUpdateIceMass = malloc(iNumBodies*sizeof(fnFinalizeUpdateIceMassModule));
  module->fnFinalizeUpdateKecc = malloc(iNumBodies*sizeof(fnFinalizeUpdateKeccModule));
  module->fnFinalizeUpdateLuminosity = malloc(iNumBodies*sizeof(fnFinalizeUpdateLuminosityModule));
  module->fnFinalizeUpdateLXUV = malloc(iNumBodies*sizeof(fnFinalizeUpdateIceMassModule));

  module->fnFinalizeUpdateMass = malloc(iNumBodies*sizeof(fnFinalizeUpdateMassModule));
  module->fnFinalizeUpdateOxygenMass = malloc(iNumBodies*sizeof(fnFinalizeUpdateOxygenMassModule));
  module->fnFinalizeUpdateOxygenMantleMass = malloc(iNumBodies*sizeof(fnFinalizeUpdateOxygenMantleMassModule));
  module->fnFinalizeUpdatePinc = malloc(iNumBodies*sizeof(fnFinalizeUpdatePincModule));
  module->fnFinalizeUpdateQinc = malloc(iNumBodies*sizeof(fnFinalizeUpdateQincModule));
  module->fnFinalizeUpdateRadius = malloc(iNumBodies*sizeof(fnFinalizeUpdateRadiusModule));
  module->fnFinalizeUpdateRot = malloc(iNumBodies*sizeof(fnFinalizeUpdateRotModule));
  module->fnFinalizeUpdateSemi = malloc(iNumBodies*sizeof(fnFinalizeUpdateSemiModule));
  module->fnFinalizeUpdateLostAngMom = malloc(iNumBodies*sizeof(fnFinalizeUpdateLostAngMomModule));
  module->fnFinalizeUpdateLostEng = malloc(iNumBodies*sizeof(fnFinalizeUpdateLostEngModule));

  module->fnFinalizeUpdateSurfaceWaterMass = malloc(iNumBodies*sizeof(fnFinalizeUpdateSurfaceWaterMassModule));
  module->fnFinalizeUpdateTemperature = malloc(iNumBodies*sizeof(fnFinalizeUpdateTemperatureModule));
  module->fnFinalizeUpdateTMan = malloc(iNumBodies*sizeof(fnFinalizeUpdateTManModule));
  module->fnFinalizeUpdateTCore = malloc(iNumBodies*sizeof(fnFinalizeUpdateTCoreModule));
  module->fnFinalizeUpdateXobl = malloc(iNumBodies*sizeof(fnFinalizeUpdateXoblModule));
  module->fnFinalizeUpdateYobl = malloc(iNumBodies*sizeof(fnFinalizeUpdateYoblModule));
  module->fnFinalizeUpdateZobl = malloc(iNumBodies*sizeof(fnFinalizeUpdateZoblModule));

  module->fnFinalizeUpdateEccX = malloc(iNumBodies*sizeof(fnFinalizeUpdateEccXModule));
  module->fnFinalizeUpdateEccY = malloc(iNumBodies*sizeof(fnFinalizeUpdateEccYModule));
  module->fnFinalizeUpdateEccZ = malloc(iNumBodies*sizeof(fnFinalizeUpdateEccZModule));
  module->fnFinalizeUpdateAngMX = malloc(iNumBodies*sizeof(fnFinalizeUpdateAngMXModule));
  module->fnFinalizeUpdateAngMY = malloc(iNumBodies*sizeof(fnFinalizeUpdateAngMYModule));
  module->fnFinalizeUpdateAngMZ = malloc(iNumBodies*sizeof(fnFinalizeUpdateAngMZModule));
  module->fnFinalizeUpdateMeanL = malloc(iNumBodies*sizeof(fnFinalizeUpdateMeanLModule));

  module->fnFinalizeUpdatePositionX = malloc(iNumBodies*sizeof(fnFinalizeUpdatePositionXModule));
  module->fnFinalizeUpdatePositionY = malloc(iNumBodies*sizeof(fnFinalizeUpdatePositionYModule));
  module->fnFinalizeUpdatePositionZ = malloc(iNumBodies*sizeof(fnFinalizeUpdatePositionZModule));
  module->fnFinalizeUpdateVelX      = malloc(iNumBodies*sizeof(fnFinalizeUpdateVelXModule));
  module->fnFinalizeUpdateVelY      = malloc(iNumBodies*sizeof(fnFinalizeUpdateVelYModule));
  module->fnFinalizeUpdateVelZ      = malloc(iNumBodies*sizeof(fnFinalizeUpdateVelZModule));

  // Function Pointer Matrices
  module->fnLogBody = malloc(iNumBodies*sizeof(fnLogBodyModule*));
  module->fnInitializeBody = malloc(iNumBodies*sizeof(fnInitializeBodyModule*));
  module->fnInitializeControl = malloc(iNumBodies*sizeof(fnInitializeControlModule*));
  module->fnInitializeUpdateTmpBody = malloc(iNumBodies*sizeof(fnInitializeUpdateTmpBodyModule*));
  module->fnCountHalts = malloc(iNumBodies*sizeof(fnCountHaltsModule*));
  module->fnReadOptions = malloc(iNumBodies*sizeof(fnReadOptionsModule*));
  module->fnVerify = malloc(iNumBodies*sizeof(fnVerifyModule*));
  module->fnVerifyHalt = malloc(iNumBodies*sizeof(fnVerifyHaltModule*));

  /* Assume no modules per body to start */
  for (iBody=0;iBody<iNumBodies;iBody++)
    module->iNumModules[iBody]=0;
}

void FinalizeModule(BODY *body,MODULE *module,int iBody) {
  int iModule=0,iNumModules = 0;

  /************************
   * ADD NEW MODULES HERE *
   ************************/

  if (body[iBody].bEqtide)
    iNumModules++;
  if (body[iBody].bDistOrb)
    iNumModules++;
  if (body[iBody].bDistRot)
    iNumModules++;
  if (body[iBody].bRadheat)
    iNumModules++;
  if (body[iBody].bThermint)
    iNumModules++;
  if (body[iBody].bAtmEsc)
    iNumModules++;
  if (body[iBody].bStellar)
    iNumModules++;
  if (body[iBody].bPoise)
    iNumModules++;
  if (body[iBody].bBinary)
    iNumModules++;
  if (body[iBody].bFlare)
    iNumModules++;
  if (body[iBody].bGalHabit)
    iNumModules++;
  if (body[iBody].bDistRes)
    iNumModules++;
  if (body[iBody].bSpiNBody)
    iNumModules++;

  module->iNumModules[iBody] = iNumModules;
  module->iaModule[iBody] = malloc(iNumModules*sizeof(int));

  module->fnLogBody[iBody] = malloc(iNumModules*sizeof(fnLogBodyModule));
  module->fnInitializeControl[iBody] = malloc(iNumModules*sizeof(fnInitializeControlModule));
  module->fnInitializeOutput[iBody] = malloc(iNumModules*sizeof(fnInitializeOutputModule));
  module->fnInitializeUpdateTmpBody[iBody] = malloc(iNumModules*sizeof(fnInitializeUpdateTmpBodyModule));

  module->fnCountHalts[iBody] = malloc(iNumModules*sizeof(fnCountHaltsModule));
  module->fnReadOptions[iBody] = malloc(iNumModules*sizeof(fnReadOptionsModule));
  module->fnVerify[iBody] = malloc(iNumModules*sizeof(fnVerifyModule));
  module->fnVerifyHalt[iBody] = malloc(iNumModules*sizeof(fnVerifyHaltModule));

  module->fnInitializeBody[iBody] = malloc(iNumModules*sizeof(fnInitializeBodyModule));
  module->fnInitializeUpdate[iBody] = malloc(iNumModules*sizeof(fnInitializeUpdateModule));

  // Finalize Primary Variable Functions
  module->fnFinalizeUpdate26AlNumCore[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate26AlNumCoreModule));
  module->fnFinalizeUpdate26AlNumMan[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate26AlNumManModule));
  module->fnFinalizeUpdate40KNumCore[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate40KNumCoreModule));
  module->fnFinalizeUpdate40KNumCrust[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate40KNumCrustModule));
  module->fnFinalizeUpdate40KNumMan[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate40KNumManModule));
  module->fnFinalizeUpdate232ThNumCore[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate232ThNumCoreModule));
  module->fnFinalizeUpdate232ThNumCrust[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate232ThNumCrustModule));
  module->fnFinalizeUpdate232ThNumMan[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate232ThNumManModule));
  module->fnFinalizeUpdate235UNumCore[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate235UNumCoreModule));
  module->fnFinalizeUpdate235UNumCrust[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate235UNumCrustModule));
  module->fnFinalizeUpdate235UNumMan[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate235UNumManModule));
  module->fnFinalizeUpdate238UNumCore[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate238UNumCoreModule));
  module->fnFinalizeUpdate238UNumCrust[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate238UNumCrustModule));
  module->fnFinalizeUpdate238UNumMan[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate238UNumManModule));

  module->fnFinalizeUpdateCBPR[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateCBPRModule));
  module->fnFinalizeUpdateCBPZ[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateCBPZModule));
  module->fnFinalizeUpdateCBPPhi[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateCBPPhiModule));
  module->fnFinalizeUpdateCBPRDot[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateCBPRDotModule));
  module->fnFinalizeUpdateCBPZDot[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateCBPZDotModule));
  module->fnFinalizeUpdateCBPPhiDot[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateCBPPhiDotModule));

  module->fnFinalizeUpdateDynEllip[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateDynEllipModule));
  module->fnFinalizeUpdateEnvelopeMass[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateEnvelopeMassModule));
  module->fnFinalizeUpdateHecc[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateHeccModule));
  module->fnFinalizeUpdateIceMass[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateIceMassModule));
  module->fnFinalizeUpdateKecc[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateKeccModule));
  module->fnFinalizeUpdateLuminosity[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateLuminosityModule));
  module->fnFinalizeUpdateLXUV[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateMassModule));
  module->fnFinalizeUpdateMass[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateMassModule));
  module->fnFinalizeUpdateOxygenMass[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateOxygenMassModule));
  module->fnFinalizeUpdateOxygenMantleMass[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateOxygenMantleMassModule));
  module->fnFinalizeUpdatePinc[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdatePincModule));
  module->fnFinalizeUpdateQinc[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateQincModule));

  module->fnFinalizeUpdateRadius[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateRadiusModule));
  module->fnFinalizeUpdateRot[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateRotModule));
  module->fnFinalizeUpdateSemi[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateSemiModule));
  module->fnFinalizeUpdateSurfaceWaterMass[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateSurfaceWaterMassModule));
  module->fnFinalizeUpdateTCore[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateTCoreModule));
  module->fnFinalizeUpdateTMan[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateTManModule));
  module->fnFinalizeUpdateXobl[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateXoblModule));
  module->fnFinalizeUpdateYobl[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateYoblModule));
  module->fnFinalizeUpdateZobl[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateZoblModule));
  module->fnFinalizeUpdateTemperature[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateTemperatureModule));
  module->fnFinalizeUpdateLostAngMom[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateLostAngMomModule));
  module->fnFinalizeUpdateLostEng[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateLostEngModule));

  module->fnFinalizeUpdateEccX[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateEccXModule));
  module->fnFinalizeUpdateEccY[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateEccYModule));
  module->fnFinalizeUpdateEccZ[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateEccZModule));
  module->fnFinalizeUpdateAngMX[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateAngMXModule));
  module->fnFinalizeUpdateAngMY[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateAngMYModule));
  module->fnFinalizeUpdateAngMZ[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateAngMZModule));
  module->fnFinalizeUpdateMeanL[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateMeanLModule));

  module->fnFinalizeUpdatePositionX[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdatePositionXModule));
  module->fnFinalizeUpdatePositionY[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdatePositionYModule));
  module->fnFinalizeUpdatePositionZ[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdatePositionZModule));
  module->fnFinalizeUpdateVelX[iBody]      = malloc(iNumModules*sizeof(fnFinalizeUpdateVelXModule));
  module->fnFinalizeUpdateVelY[iBody]      = malloc(iNumModules*sizeof(fnFinalizeUpdateVelYModule));
  module->fnFinalizeUpdateVelZ[iBody]      = malloc(iNumModules*sizeof(fnFinalizeUpdateVelZModule));

  for(iModule = 0; iModule < iNumModules; iModule++) {
    /* Initialize all module functions pointers to point to their respective
       NULL function. The modules that need actual function will replace them
       in AddModule. */

    module->fnInitializeControl[iBody][iModule] = &InitializeControlNULL;
    module->fnInitializeUpdateTmpBody[iBody][iModule] = &InitializeUpdateTmpBodyNULL;
    module->fnInitializeBody[iBody][iModule] = &InitializeBodyNULL;

    module->fnFinalizeUpdate26AlNumCore[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate26AlNumMan[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate40KNumCore[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate40KNumCrust[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate40KNumMan[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate232ThNumCore[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate232ThNumCrust[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate232ThNumMan[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate235UNumCore[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate235UNumCrust[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate235UNumMan[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate238UNumCore[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate238UNumCrust[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate238UNumMan[iBody][iModule] = &FinalizeUpdateNULL;

    module->fnFinalizeUpdateCBPR[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateCBPZ[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateCBPPhi[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateCBPRDot[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateCBPZDot[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateCBPPhiDot[iBody][iModule] = &FinalizeUpdateNULL;

    module->fnFinalizeUpdateDynEllip[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateEnvelopeMass[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateHecc[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateIceMass[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateKecc[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateLuminosity[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateLXUV[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateMass[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateOxygenMass[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateOxygenMantleMass[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdatePinc[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateQinc[iBody][iModule] = &FinalizeUpdateNULL;

    module->fnFinalizeUpdateRadius[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateRot[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateSemi[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateSurfaceWaterMass[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateTemperature[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateTMan[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateTCore[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateXobl[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateYobl[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateZobl[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateLostAngMom[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateLostEng[iBody][iModule] = &FinalizeUpdateNULL;

    module->fnFinalizeUpdateEccX[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateEccY[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateEccZ[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateAngMX[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateAngMY[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateAngMZ[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateMeanL[iBody][iModule] = &FinalizeUpdateNULL;

    module->fnFinalizeUpdatePositionX[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdatePositionY[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdatePositionZ[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateVelX[iBody][iModule]      = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateVelY[iBody][iModule]      = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateVelZ[iBody][iModule]      = &FinalizeUpdateNULL;
  }

  /************************
   * ADD NEW MODULES HERE *
   ************************/

  iModule = 0;
  if (body[iBody].bEqtide) {
    AddModuleEqtide(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = EQTIDE;
  }
  if (body[iBody].bDistOrb) {
    AddModuleDistOrb(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = DISTORB;
  }
   if (body[iBody].bDistRot) {
    AddModuleDistRot(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = DISTROT;
  }
  if (body[iBody].bRadheat) {
    AddModuleRadheat(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = RADHEAT;
  }
  if (body[iBody].bThermint) {
      AddModuleThermint(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = THERMINT;
  }
  if (body[iBody].bAtmEsc) {
    AddModuleAtmEsc(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = ATMESC;
  }
  if (body[iBody].bStellar) {
    AddModuleStellar(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = STELLAR;
  }
  if (body[iBody].bPoise) {
    AddModulePoise(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = POISE;
  }
  if (body[iBody].bBinary) {
    AddModuleBinary(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = BINARY;
  }
  if (body[iBody].bFlare) {
    AddModuleFlare(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = FLARE;
  }
  if (body[iBody].bGalHabit) {
    AddModuleGalHabit(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = GALHABIT;
  }
  if (body[iBody].bDistRes) {
    AddModuleDistRes(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = DISTRES;
  }
  if (body[iBody].bSpiNBody) {
    AddModuleSpiNBody(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = SPINBODY;
  }
}

void ReadModules(BODY *body,CONTROL *control,FILES *files,MODULE *module,OPTIONS *options,int iFile){
  int iNumIndices=0,iNumLines=0,iModule;
  int *lTmp;
  char saTmp[MAXARRAY][OPTLEN];

  lTmp=malloc(MAXLINES*sizeof(int));

  AddOptionStringArray(files->Infile[iFile].cIn,options->cName,saTmp,&iNumIndices,&iNumLines,lTmp,control->Io.iVerbose);
  if (lTmp[0] >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp[0],control->Io.iVerbose);
    if (iNumIndices == 0) {
      if (control->Io.iVerbose >= VERBERR)
        fprintf(stderr,"ERROR: No modules input to option %s.\n",options->cName);
      LineExit(files->Infile[iFile].cIn,lTmp[0]);
    }

    /* The iBitSum field is to check that every output parameter is part
       of the input modules. The variables EQTIDE, RADHEAT, etc. are set
       in vpanet.h. Each module-specific parameter is given the appropriate
       bit in InitializeOutput. In ReadOutputOrder the field
       output->iModuleBit is compared bitwise to module->iBitSum.
       Parameters that can be specified for multiple modules are set to 1.
       iBitSum for each body is set 1 in InitializeModule.
    */

    for (iModule=0;iModule<iNumIndices;iModule++) {

      /************************
       * ADD NEW MODULES HERE *
       ************************/

      if (memcmp(sLower(saTmp[iModule]),"eqtide",6) == 0) {
        body[iFile-1].bEqtide = 1;
	module->iBitSum[iFile-1] += EQTIDE;
      } else if (memcmp(sLower(saTmp[iModule]),"radheat",7) == 0) {
        body[iFile-1].bRadheat = 1;
	module->iBitSum[iFile-1] += RADHEAT;
      } else if (memcmp(sLower(saTmp[iModule]),"distorb",8) == 0) {
        body[iFile-1].bDistOrb = 1;
	module->iBitSum[iFile-1] += DISTORB;
      } else if (memcmp(sLower(saTmp[iModule]),"distrot",7) == 0) {
        body[iFile-1].bDistRot = 1;
	module->iBitSum[iFile-1] += DISTROT;
      } else if (memcmp(sLower(saTmp[iModule]),"thermint",8) == 0) {
	body[iFile-1].bThermint = 1;
	module->iBitSum[iFile-1] += THERMINT;
      } else if (memcmp(sLower(saTmp[iModule]),"atmesc",6) == 0) {
        body[iFile-1].bAtmEsc = 1;
	module->iBitSum[iFile-1] += ATMESC;
      } else if (memcmp(sLower(saTmp[iModule]),"stellar",7) == 0) {
	body[iFile-1].bStellar = 1;
	module->iBitSum[iFile-1] += STELLAR;
      } else if (memcmp(sLower(saTmp[iModule]),"poise",5) == 0) {
	body[iFile-1].bPoise = 1;
	module->iBitSum[iFile-1] += POISE;
      } else if (memcmp(sLower(saTmp[iModule]),"binary",6) == 0) {
        body[iFile-1].bBinary = 1;
	module->iBitSum[iFile-1] += BINARY;
      } else if (memcmp(sLower(saTmp[iModule]),"flare",5) == 0) {
	body[iFile-1].bFlare = 1;
	module->iBitSum[iFile-1] += FLARE;
      } else if (memcmp(sLower(saTmp[iModule]),"galhabit",8) == 0) {
	body[iFile-1].bGalHabit = 1;
	module->iBitSum[iFile-1] += GALHABIT;
      } else if (memcmp(sLower(saTmp[iModule]),"distres",7) == 0) {
        body[iFile-1].bDistRes = 1;
	module->iBitSum[iFile-1] += DISTRES;
      } else if (memcmp(sLower(saTmp[iModule]),"spinbody",8) == 0) {
  body[iFile-1].bSpiNBody = 1;
  module->iBitSum[iFile-1] += SPINBODY;
      } else {
        if (control->Io.iVerbose >= VERBERR)
          fprintf(stderr,"ERROR: Unknown Module %s provided to %s.\n",saTmp[iModule],options->cName);
        LineExit(files->Infile[iFile].cIn,lTmp[0]);
      }
    }
    UpdateFoundOptionMulti(&files->Infile[iFile],options,lTmp,iNumLines,iFile);

    } else {
    if (control->Io.iVerbose >= VERBERR && iFile > 0)
      fprintf(stderr,"WARNING: %s not present in file %s. No evolution will occur for this body.\n",options->cName,files->Infile[iFile].cIn);
  }
  free(lTmp);
}

void PrintModuleList(FILE *file,int iBitSum) {

  if (iBitSum & ATMESC)
    fprintf(file,"ATMESC ");
  if (iBitSum & BINARY)
    fprintf(file,"BINARY ");
  if (iBitSum & DISTORB)
    fprintf(file,"DISTORB ");
  if (iBitSum & DISTROT)
    fprintf(file,"DISTROT ");
  if (iBitSum & EQTIDE)
    fprintf(file,"EQTIDE ");
  if (iBitSum & FLARE)
    fprintf(file,"FLARE ");
  if (iBitSum & GALHABIT)
    fprintf(file,"GALHABIT ");
  if (iBitSum & POISE)
    fprintf(file,"POISE ");
  if (iBitSum & RADHEAT)
    fprintf(file,"RADHEAT ");
  if (iBitSum & STELLAR)
    fprintf(file,"STELLAR ");
  if (iBitSum & THERMINT)
    fprintf(file,"THERMINT ");
  if (iBitSum & SPINBODY)
    fprintf(file,"SPINBODY ");

}

void InitializeBodyModules(BODY **body,int iNumBodies) {
  int iBody;

  for (iBody=0;iBody<iNumBodies;iBody++) {
      (*body)[iBody].bAtmEsc = 0;
      (*body)[iBody].bBinary = 0;
      (*body)[iBody].bDistOrb = 0;
      (*body)[iBody].bDistRot = 0;
      (*body)[iBody].bEqtide = 0;
      (*body)[iBody].bFlare = 0;
      (*body)[iBody].bGalHabit = 0;
      (*body)[iBody].bPoise = 0;
      (*body)[iBody].bRadheat = 0;
      (*body)[iBody].bStellar = 0;
      (*body)[iBody].bThermint = 0;
      (*body)[iBody].bDistRes = 0;
      (*body)[iBody].bSpiNBody = 0;
  }
}

/*
 * Verify multi-module dependencies
 */


void VerifyModuleMultiDistOrbDistRot(BODY *body,UPDATE *update,CONTROL *control,FILES *files,OPTIONS *options,int iBody,int *iModuleProps,int *iModuleForce) {

  if (body[iBody].bDistRot) {
    if (!body[iBody].bDistOrb) {
      if (!body[iBody].bReadOrbitData) {
        fprintf(stderr,"ERROR: Module DISTROT selected for %s, but DISTORB not selected and bReadOrbitData = 0.\n",body[iBody].cName);
        exit(EXIT_INPUT);
      }
    } else {
      if (body[iBody].bReadOrbitData) {
        fprintf(stderr,"ERROR: Cannot set both DISTORB and bReadOrbitData for body %s.\n",body[iBody].cName);
        exit(EXIT_INPUT);
      }
    }
  }
}

void VerifyModuleMultiEqtideDistRot(BODY *body,UPDATE *update,CONTROL *control,FILES *files,OPTIONS *options,int iBody,int *iModuleProps,int *iModuleForce) {

  if (body[iBody].bDistRot) {
    if (body[iBody].bEqtide) {
      if (body[iBody].bReadOrbitData) {
        fprintf(stderr,"ERROR: Cannot set both EQTIDE and bReadOrbitData for body %s.\n",body[iBody].cName);
        exit(EXIT_INPUT);
      }
    }
  }
}

void VerifyModuleMultiRadheatThermint(BODY *body,UPDATE *update,CONTROL *control,FILES *files,OPTIONS *options,int iBody,int *iModuleProps,int *iModuleForce) {

  /* This will need modification if material can move between layers */

  if (body[iBody].bThermint) {
    if (!body[iBody].bRadheat) {
      if (control->Io.iVerbose > VERBINPUT)
        fprintf(stderr,"WARNING: Module THERMINT selected for %s, but RADHEAT not selected.\n",body[iBody].cName);
      body[iBody].dRadPowerCore = 0.;
      body[iBody].dRadPowerCrust = 0.;
      body[iBody].dRadPowerMan = 0.;
    } else
      control->fnPropsAuxMulti[iBody][(*iModuleProps)++] = &PropsAuxRadheatThermint;
  }
}

void VerifyModuleMultiEqtideThermint(BODY *body,UPDATE *update,CONTROL *control,FILES *files,MODULE *module,OPTIONS *options,int iBody,int *iModuleProps,int *iModuleForce) {
  int iEqtide;

  // Eqtide, not thermint
  if (body[iBody].bEqtide) {
    if (!body[iBody].bThermint) {
      /* Eqtide called, but not thermint. Make sure that bOceanTides=0 and
	 check if dTidalQOcean and dK2Ocean are set. These should only be set if THERMINT
	 selected. */
      if (body[iBody].bOceanTides) {
	if (control->Io.iVerbose >= VERBINPUT)
	  fprintf(stderr,"ERROR: %s set, but module THERMINT not selected.\n",options[OPT_OCEANTIDES].cName);
        exit(EXIT_INPUT);
      }
      if (options[OPT_TIDALQOCEAN].iLine[iBody+1] > -1) {
	if (control->Io.iVerbose >= VERBINPUT)
	  fprintf(stderr,"ERROR: %s set, but module THERMINT not selected.\n",options[OPT_TIDALQOCEAN].cName);
	exit(EXIT_INPUT);
        }
      if (options[OPT_K2OCEAN].iLine[iBody+1] > -1) {
        if (control->Io.iVerbose >= VERBINPUT)
          fprintf(stderr,"ERROR: %s set, but module THERMINT not selected.\n",options[OPT_K2OCEAN].cName);
        exit(EXIT_INPUT);
      }

      // Set Im(k_2) here
      body[iBody].dImK2=body[iBody].dK2/body[iBody].dTidalQ;

      // No ocean contribution if not using thermint
      body[iBody].dImK2Ocean = 0.0;
      body[iBody].dK2Ocean = 0.0;
      body[iBody].dTidalQOcean = -1.0;

      // Now set the "Man" functions as the WriteTidalQ uses them
      // This ensures that the write function works
      body[iBody].dImk2Man = body[iBody].dImK2;
      body[iBody].dK2Man = body[iBody].dK2;
    } else { // Thermint and Eqtide called

      // If dTidalQ or K2 set, ignore/warn user as thermint computes these
      if (options[OPT_TIDALQ].iLine[iBody+1] > -1) {
        if (control->Io.iVerbose >= VERBINPUT)
          fprintf(stderr,"WARNING: %s set, but module THERMINT computes it.  Inputted value ignored.\n",options[OPT_TIDALQ].cName);
      }
      if (options[OPT_K2].iLine[iBody+1] > -1) {
        if (control->Io.iVerbose >= VERBINPUT)
          fprintf(stderr,"WARNING: %s set, but module THERMINT computes it.  Inputted value ignored.\n",options[OPT_K2].cName);
      }

      /* When Thermint and Eqtide are called together, care must be taken as
         Im(k_2) must be known in order to calculate TidalZ. As the individual
         module PropsAux are called prior to PropsAuxMulti, we must call the
         "PropsAuxEqtide" function after Im(k_2) is called. Thus, we replace
         "PropsAuxEqtide" with PropsAuxNULL and call "PropsAuxEqtide" in
         PropsAuxEqtideThermint. */

      // If using ocean tides...
      //Convert Q_ocean -> Im(k2)_ocean
      if(body[iBody].bOceanTides)
      {
        // Make sure both dK2Ocean AND dTidalQOcean are set, otherwise exit
        if(!(options[OPT_TIDALQOCEAN].iLine[iBody+1] > -1 && options[OPT_K2OCEAN].iLine[iBody+1] > -1))
        {
          fprintf(stderr,"ERROR: %s and/or %s not set.\n",options[OPT_OCEANTIDES].cName,options[OPT_K2OCEAN].cName);
          fprintf(stderr,"Must both be set when using EQTIDE and THERMINT with bOceanTides == True.\n");
          exit(EXIT_INPUT);
        }

        // Otherwise, we're good! set ImK2 for the ocean component
        body[iBody].dImK2Ocean = body[iBody].dK2Ocean/body[iBody].dTidalQOcean;
      }
      // If you're not using bOceanTides and Ocean params are set, exit
      else
      {
        if(options[OPT_TIDALQOCEAN].iLine[iBody+1] > -1 || options[OPT_K2OCEAN].iLine[iBody+1] > -1)
        {
          if (control->Io.iVerbose >= VERBINPUT)
          {
            fprintf(stderr,"ERROR: %s or %s set, but bOceanTides == 0.\n",options[OPT_TIDALQOCEAN].cName,options[OPT_K2OCEAN].cName);
            exit(EXIT_INPUT);
          }
        }

        // No ocean contribution
        body[iBody].dImK2Ocean = 0.0;
        body[iBody].dK2Ocean = 0.0;
        body[iBody].dTidalQOcean = -1.0;
      }

      iEqtide = fiGetModuleIntEqtide(module,iBody);
      control->fnPropsAux[iBody][iEqtide] = &PropsAuxNULL;
      control->fnPropsAuxMulti[iBody][(*iModuleProps)++] = &PropsAuxEqtideThermint;
    }
  }

  /*
  else if (body[iBody].bThermint) { // eqtide not called, but thermint is
    //exit(1);

    printf("%d\n",iBody);
    fflush(stdout);
    body[iBody].dImk2Man = fdImk2Man(body,iBody);
  }
  */
}

void VerifyModuleMultiEqtideDistOrb(BODY *body,UPDATE *update,CONTROL *control,FILES *files,MODULE *module,OPTIONS *options,int iBody,int *iModuleProps,int *iModuleForce) {
  if (body[iBody].bEqtide) {
    if (body[iBody].bDistOrb) {
      control->fnForceBehaviorMulti[iBody][(*iModuleForce)++] = &ForceBehaviorEqtideDistOrb;
    }
  }
}

void VerifyModuleMultiEqtideStellar(BODY *body,UPDATE *update,CONTROL *control,FILES *files,MODULE *module,OPTIONS *options,int iBody,int *iModuleProps,int *iModuleForce) {
  if (body[iBody].bEqtide) {
    if (body[iBody].bStellar) {

      // If you're using stellar and eqtide and this isn't the primary body, you
      // MUST use binary (binary stars!)
      if(iBody > 0 && !body[iBody].bBinary)
      {
        if(control->Io.iVerbose >= VERBINPUT)
          fprintf(stderr,"ERROR: If both stellar AND eqtide are set and iBody > 0, MUST use binary!\n");
        exit(EXIT_INPUT);
      }

      // Can't have any ocean, envelope tidal parameters set
      // Body is a star, but has an ocean or an envelope!
      if(body[iBody].bOceanTides || body[iBody].bEnvTides)
      {
        if(control->Io.iVerbose >= VERBINPUT)
          fprintf(stderr,"ERROR: If both stellar AND eqtide are set, body cannot have bOceanTides or bEnvTides set!\n");
        LineExit(files->Infile[iBody+1].cIn,options[OPT_MODULES].iLine[iBody+1]);
      }

      if (options[OPT_TIDALQOCEAN].iLine[iBody+1] > -1) {
	    if (control->Io.iVerbose >= VERBINPUT)
	      fprintf(stderr,"ERROR: %s set, but this body is a star!.\n",options[OPT_TIDALQOCEAN].cName);
	    exit(EXIT_INPUT);
      }
      if (options[OPT_K2OCEAN].iLine[iBody+1] > -1) {
        if (control->Io.iVerbose >= VERBINPUT)
          fprintf(stderr,"ERROR: %s set, but this body is a star!.\n",options[OPT_K2OCEAN].cName);
        exit(EXIT_INPUT);
      }
      if (options[OPT_TIDALQENV].iLine[iBody+1] > -1) {
        if (control->Io.iVerbose >= VERBINPUT)
          fprintf(stderr,"ERROR: %s set, but this body is a star!.\n",options[OPT_TIDALQENV].cName);
        exit(EXIT_INPUT);
        }
        if (options[OPT_K2ENV].iLine[iBody+1] > -1) {
          if (control->Io.iVerbose >= VERBINPUT)
            fprintf(stderr,"ERROR: %s set, but this body is a star!.\n",options[OPT_K2ENV].cName);
          exit(EXIT_INPUT);
        }

      // ALl the options are ok! Add in the necessary AuxProps
      control->fnPropsAuxMulti[iBody][(*iModuleProps)++] = &PropsAuxEqtideStellar;
    }
  }
}

void VerifyModuleMultiAtmescEqtide(BODY *body,UPDATE *update,CONTROL *control,FILES *files,MODULE *module,OPTIONS *options,int iBody,int *iModuleProps,int *iModuleForce) {
  /* Ensure that if using Lopez et al radius models, ATMESC uses Lopez et al radius for atmespheric escape
   * while EQTIDE uses a "tidal radius" as it is likely that the radius of the envelope does not really
   * impact tides since the tidal evolution has such a strong (r^5) radius dependent.  Effectively, we assume
   * that the core/ocean size of stuff controls that evolution while the atmosphere contributes to the Tidal
   * Q, k_2 and Im(k_2) for the world
   */

   // dImK2Env has no read options, so must initialize here!
   body[iBody].dImK2Env = 1;

  // If this is the star (body 0 or body 1 in binary), tidal radius == radius
  if(iBody == 0 || (body[iBody].bBinary && iBody == 1) || (body[iBody].bStellar))
  {
    body[iBody].dTidalRadius = body[iBody].dRadius;
     return;
  }

  if(body[iBody].bEqtide)
  {
    // CTL hack.  Pretty sure EQTIDE CTL is broken, but this will prevent additional hiccups
    // Ignore everything after this
    if(control->Evolve.iEqtideModel == CTL)
    {
      body[iBody].dTidalRadius = body[iBody].dRadius;
      return;
    }

    // Using ATMESC?
    if(body[iBody].bAtmEsc)
    {

      // if user wants to include tides due to envelope: (do same with oceans)
      if (body[iBody].bEnvTides) {
        // they better have defined k2Env, tidalqenv, denvmass
        if (!(options[OPT_TIDALQENV].iLine[iBody+1] > -1)) {
          fprintf(stderr,"ERROR: if bEnvTides == 1, must specify %s.\n",options[OPT_TIDALQENV].cName);
          exit(EXIT_INPUT);
        }
        // k2env not set
        else if (!(options[OPT_K2ENV].iLine[iBody+1] > -1)) {
          fprintf(stderr,"ERROR: if bEnvTides == 1, must specify %s.\n",options[OPT_K2ENV].cName);
          exit(EXIT_INPUT);
        }
        // envmass not set
        else if (!(options[OPT_ENVELOPEMASS].iLine[iBody+1] > -1)) {
          fprintf(stderr, "ERROR: if bEnvTides == 1, must specify %s.\n",options[OPT_ENVELOPEMASS].cName);
          exit(EXIT_INPUT);
        }
      }

      if (body[iBody].bOceanTides) {
        // they better have defined k2Ocean, tidalqocean, dSurfaceWaterMass
        if (!(options[OPT_TIDALQOCEAN].iLine[iBody+1] > -1)) {
          fprintf(stderr, "ERROR: if bOceanTides == 1, must specify %s.\n",options[OPT_TIDALQOCEAN].cName);
          exit(EXIT_INPUT);
        }
        else if (!(options[OPT_SURFACEWATERMASS].iLine[iBody+1] > -1)) {
          fprintf(stderr, "ERROR: if bOceanTides == 1, must specify %s.\n",options[OPT_SURFACEWATERMASS].cName);
          exit(EXIT_INPUT);
        }
        else if (!(options[OPT_K2OCEAN].iLine[iBody+1] > -1)) {
          fprintf(stderr, "ERROR: if bOceanTides == 1, must specify %s.\n",options[OPT_K2OCEAN].cName);
          exit(EXIT_INPUT);
        }
      }
      // now lets check there's actually an envelope
      // there is not an envelope!!
      if (!(body[iBody].dEnvelopeMass > body[iBody].dMinEnvelopeMass)) {
        body[iBody].bEnv = 0;
      }
      else {
        body[iBody].bEnv = 1;
        body[iBody].dImK2Env = body[iBody].dK2Env / body[iBody].dTidalQEnv;
      }
      // what about an ocean?
      if (!(body[iBody].dSurfaceWaterMass > body[iBody].dMinSurfaceWaterMass)) {
        body[iBody].bOcean = 0;
      }
      else {
        body[iBody].bOcean = 1;
        body[iBody].dImK2Ocean = body[iBody].dK2Ocean / body[iBody].dTidalQOcean;
      }

      // there's definitely at least gonna be some rock...
      body[iBody].dImK2Rock = body[iBody].dK2Rock / body[iBody].dTidalQRock;

      // if there is an envelope/ocean, we calculate ImK2Env/ImK2Ocean
      if (body[iBody].bEnv && (body[iBody].dTidalQ != body[iBody].dTidalQEnv)) {
        fprintf(stderr,"Using dTidalQEnv for %s.\n",body[iBody].cName);
        body[iBody].dTidalQ = body[iBody].dTidalQEnv;
        body[iBody].dK2 = body[iBody].dK2Env;
        body[iBody].dImK2Env = body[iBody].dK2Env / body[iBody].dTidalQEnv;
        body[iBody].dImK2 = body[iBody].dImK2Env;
      }
      else {
        if (body[iBody].bOcean && (body[iBody].dTidalQ != body[iBody].dTidalQOcean)) {
          fprintf(stderr,"Using dTidalQOcean for %s.\n",body[iBody].cName);
          body[iBody].dTidalQ = body[iBody].dTidalQOcean;
          body[iBody].dImK2Ocean = body[iBody].dK2Ocean / body[iBody].dTidalQOcean;
          body[iBody].dImK2 = body[iBody].dImK2Ocean;
          body[iBody].dK2 = body[iBody].dK2Ocean;
        }
        else if (!body[iBody].bEnv && !body[iBody].bOcean && (body[iBody].dTidalQ != body[iBody].dTidalQRock) && (iBody != 0)){
          fprintf(stderr,"Using dTidalQRock for %s.\n",body[iBody].cName);
          // now we just use dTidalQRock and dK2Rock
          body[iBody].dImK2Rock = body[iBody].dK2Rock / body[iBody].dTidalQRock;
          body[iBody].dTidalQ = body[iBody].dTidalQRock;
          body[iBody].dK2 = body[iBody].dK2Rock;
          body[iBody].dImK2 = body[iBody].dImK2Rock;
        }
    }
      // Using tidal radus
      if(body[iBody].bUseTidalRadius)
      {
        // If any tidal radius option is set, the other must be set as well!
        if(!((options[OPT_TIDALRADIUS].iLine[iBody+1] > -1) && (options[OPT_TIDALRADIUS].iLine[iBody+1] > -1)))
        {
          fprintf(stderr,"ERROR: if bTidalRadius == 1, must set %s.\n",options[OPT_TIDALRADIUS].cName);
          exit(EXIT_INPUT);
        }
      }


      // Not using tidal radius
      else
      {
        // Since no tidal radius specified, dRadius better be (or a radius evolution model or a mass radius relation)
        if(!(options[OPT_RADIUS].iLine[iBody+1] > -1) && !(options[OPT_PLANETRADIUSMODEL].iLine[iBody+1] > -1) && !(options[OPT_MASSRAD].iLine[iBody+1] > -1))
        {
          fprintf(stderr,"ERROR: Using EQTIDE and bUseTidalRadius == 0 but %s or %s not set!\n",options[OPT_RADIUS].cName,options[OPT_PLANETRADIUSMODEL].cName);
          exit(EXIT_INPUT);
        }

        // If dTidalRadius set, warn user since it's not considered
        if(options[OPT_TIDALRADIUS].iLine[iBody+1] > -1)
        {
          if(control->Io.iVerbose >= VERBINPUT)
          {
            fprintf(stderr,"WARNING: %s set but disregarded since bUseTidalRadius == 0.\n",options[OPT_TIDALRADIUS].cName);
          }
        }

        // No tidal radius given -> just use specified radius
        body[iBody].dTidalRadius = body[iBody].dRadius;
      }

      // now we need to do verify steps to make sure everything is set:
      // Sets behavior for changing between dTidalQEnv, dTidalQOcean, and dTidalQRock
      control->fnForceBehaviorMulti[iBody][(*iModuleForce)++] = &ForceBehaviorEqtideAtmesc;

      // Set a PropsAuxMultiAtmescEqtide here that controls dRadius/dTidalRadius
      control->fnPropsAuxMulti[iBody][(*iModuleProps)++] = &PropsAuxAtmescEqtide;

    }


    // Not using ATMESC
    else
    {
      // Using tidal radius without atmesc doesn't make sense, just need to set radius
      // Ignore if using stellar with some radius relation
      if(!(options[OPT_RADIUS].iLine[iBody+1] > -1))
      {
        fprintf(stderr,"ERROR: Using EQTIDE but %s not set!\n",options[OPT_RADIUS].cName);
        exit(EXIT_INPUT);
      }

      // If dTidalRadius or bUseTidalRadius set, ignore and warn user as they do nothing
      if((options[OPT_USETIDALRADIUS].iLine[iBody+1] > -1) || (options[OPT_TIDALRADIUS].iLine[iBody+1] > -1))
      {
        if(control->Io.iVerbose >= VERBINPUT)
        {
          fprintf(stderr,"WARNING: %s and/or %s set for EQTIDE while ATMESC not used and hence will be ignored.\n",options[OPT_USETIDALRADIUS].cName,options[OPT_TIDALRADIUS].cName);
        }
      }

      // TidalRadius == radius as without ATMESC, planet radius doesn't evolve
      body[iBody].dTidalRadius = body[iBody].dRadius;
      }
    }
  }
void VerifyModuleMultiAtmescEqtideThermint(BODY *body,UPDATE *update,CONTROL *control,FILES *files,MODULE *module,OPTIONS *options,int iBody,int *iModuleProps,int *iModuleForce) {

  // If you're using alllll of these, include the force behavior!
  // Also, you MUST have surface water information set if you're using bOceanTides
  // Note: VerifyEqtideThermint handles all things oceans

  // dImK2Env has no ReadOption, so we must initialize it here.
  body[iBody].dImK2Env = 1;

  if(body[iBody].bEqtide)
  {
    if(body[iBody].bThermint)
    {
      if(body[iBody].bAtmEsc)
      {
        // If modelling envelope tides
        if(body[iBody].bEnvTides)
        {
          // Make sure both dK2Env AND dTidalQEnv are set, otherwise exit
          if(!(options[OPT_TIDALQENV].iLine[iBody+1] > -1 && options[OPT_K2ENV].iLine[iBody+1] > -1))
          {
            fprintf(stderr,"ERROR: %s and/or %s not set.\n",options[OPT_TIDALQENV].cName,options[OPT_K2ENV].cName);
            fprintf(stderr,"Must both be set when using EQTIDE, THERMINT and ATMESC with bEnvTides == True.\n");
            exit(EXIT_INPUT);
          }

          // Otherwise, we're good! set ImK2 for the envelope component
          body[iBody].dImK2Env = body[iBody].dK2Env/body[iBody].dTidalQEnv;
        }
        // Not modelling envelope tides
        else
        {
          // Envelope tidal parameters can't be set
          if(options[OPT_TIDALQENV].iLine[iBody+1] > -1 || options[OPT_K2ENV].iLine[iBody+1] > -1)
          {
            if (control->Io.iVerbose >= VERBINPUT)
            {
              fprintf(stderr,"ERROR: %s or %s set, but bEnvTides == 0.\n",options[OPT_TIDALQENV].cName,options[OPT_K2ENV].cName);
              exit(EXIT_INPUT);
            }
          }

          // Zero things out so envelope can't play a role
          body[iBody].dK2Env = 0.0;
          body[iBody].dImK2Env = 0.0;
          body[iBody].dTidalQEnv = -1.0;
        }

        // Set function pointers so models play nice

        // Set force behavior
        control->fnForceBehaviorMulti[iBody][(*iModuleForce)++] = &ForceBehaviorAtmescEqtideThermint;

        // Switch PropAuxEqtideThermint -> PropsAuxAtmescEqtideThermint
        control->fnPropsAuxMulti[iBody][(*iModuleProps)++] = &PropsAuxAtmescEqtideThermint;
      }
      // No AtmEsc
      else
      {
        // Can't have any tidal envelope parameters set
        if(options[OPT_TIDALQENV].iLine[iBody+1] > -1 || options[OPT_K2ENV].iLine[iBody+1] > -1)
        {
          if (control->Io.iVerbose >= VERBINPUT)
          {
            fprintf(stderr,"ERROR: %s or %s set, but bOceanTides == 0.\n",options[OPT_TIDALQENV].cName,options[OPT_K2ENV].cName);
            exit(EXIT_INPUT);
          }
        }

        // Zero things out so envelope can't play a role
        body[iBody].dK2Env = 0.0;
        body[iBody].dImK2Env = 0.0;
        body[iBody].dTidalQEnv = -1.0;
      }
    }
  }

}

void VerifyModuleMultiFlareStellar(BODY *body,UPDATE *update,CONTROL *control,FILES *files,MODULE *module,OPTIONS *options,int iBody,int *iModuleProps,int *iModuleForce) {

  if (body[iBody].bFlare) {
    if (!body[iBody].bStellar) {
      fprintf(stderr,"ERROR: Must include module STELLAR to run module FLARE.\n");
      LineExit(files->Infile[iBody+1].cIn,options[OPT_MODULES].iLine[iBody+1]);
    } else
      control->fnPropsAuxMulti[iBody][(*iModuleProps)++] = &PropsAuxFlareStellar;
  }
}

/*
 * Binary + Stellar coupling.  If using binary, only 1st 2 bodies (0, 1) can be stars
 */
void VerifyModuleMultiBinaryStellar(BODY *body,UPDATE *update,CONTROL *control,FILES *files,MODULE *module,OPTIONS *options,int iBody,int *iModuleProps,int *iModuleForce) {

  if (body[iBody].bBinary) {
    if (body[iBody].bStellar) {
      if(iBody > 1) {
        fprintf(stderr,"ERROR: Only bodies 0 and 1 can be stars when using binary!\n");
        LineExit(files->Infile[iBody+1].cIn,options[OPT_MODULES].iLine[iBody+1]);
      }
    }
  }
}

/*
 * Coupling Binary, Eqtide, AND stellar
 */
void VerifyModuleMultiBinaryEqtideStellar(BODY *body, UPDATE *update, CONTROL *control,FILES *files,MODULE *module,OPTIONS *options,int iBody,int *iModuleProps,int *iModuleForce) {

  if (body[iBody].bBinary) {
    if (body[iBody].bStellar) {
      if (body[iBody].bEqtide) {
        // TODO ?
        }
      }
    }
  }

/*
 * Binary + Eqtide: If using both, only stars (iBodyType == 1, iBody <= 1) can use eqtide
 */
void VerifyModuleMultiBinaryEqtide(BODY *body,UPDATE *update,CONTROL *control,FILES *files,MODULE *module,OPTIONS *options,int iBody,int *iModuleProps,int *iModuleForce)
{
  // If binary AND eqtide are called for a body, the body MUST be a star
  if(body[iBody].bBinary) {
    if(body[iBody].bEqtide) {
      // Body isn't a star!
      if(body[iBody].iBodyType != 1 || iBody > 1) {
        fprintf(stderr,"ERROR: If both binary AND eqtide are used for a body, the body MUST be a star.\n");
        fprintf(stderr,"Errant body iBody, bBinary, bEqtide:, bStellar %d, %d, %d, %d.\n",iBody,body[iBody].bBinary,body[iBody].bEqtide,body[iBody].bStellar);
        LineExit(files->Infile[iBody+1].cIn,options[OPT_MODULES].iLine[iBody+1]);
      }
    }
  }
}

void VerifyModuleMultiEqtideDistorb(BODY *body,UPDATE *update,CONTROL *control,FILES *files,MODULE *module,OPTIONS *options,int iBody,int *iModuleProps,int *iModuleForce) {
  if (body[iBody].bEqtide || body[iBody].bDistOrb)
      control->fnPropsAuxMulti[iBody][(*iModuleProps)++] = &PropsAuxEqtideDistorb;
}


void VerifyModuleMulti(BODY *body,UPDATE *update,CONTROL *control,FILES *files,MODULE *module,OPTIONS *options,int iBody,fnUpdateVariable ****fnUpdate) {

  int iNumMultiProps=0,iNumMultiForce=0;

  if (module->iNumModules[iBody] > 0) {
    /* XXX Note that the number of elements here is really a permutation,
       but this should work for a while. */
    control->fnPropsAuxMulti[iBody] = malloc(2*module->iNumModules[iBody]*sizeof(fnPropsAuxModule*));
    control->fnForceBehaviorMulti[iBody] = malloc(2*module->iNumModules[iBody]*sizeof(fnForceBehaviorModule*));
  }

  /* Now verify. Even if only module is called, we still need to call
     these functions as some default behavior is set if other modules aren't
     called. */

  VerifyModuleMultiDistOrbDistRot(body,update,control,files,options,iBody,&iNumMultiProps,&iNumMultiForce);

  VerifyModuleMultiEqtideDistRot(body,update,control,files,options,iBody,&iNumMultiProps,&iNumMultiForce);

  VerifyModuleMultiRadheatThermint(body,update,control,files,options,iBody,&iNumMultiProps,&iNumMultiForce);

  VerifyModuleMultiEqtideDistOrb(body,update,control,files,module,options,iBody,&iNumMultiProps,&iNumMultiForce);

  VerifyModuleMultiAtmescEqtide(body,update,control,files,module,options,iBody,&iNumMultiProps,&iNumMultiForce);

  VerifyModuleMultiEqtideThermint(body,update,control,files,module,options,iBody,&iNumMultiProps,&iNumMultiForce);

  // Always call after VerifyModuleMultiEqtideThermint !!
  VerifyModuleMultiAtmescEqtideThermint(body,update,control,files,module,options,iBody,&iNumMultiProps,&iNumMultiForce);

  VerifyModuleMultiFlareStellar(body,update,control,files,module,options,iBody,&iNumMultiProps,&iNumMultiForce);

  VerifyModuleMultiBinaryEqtide(body,update,control,files,module,options,iBody,&iNumMultiProps,&iNumMultiForce);

  VerifyModuleMultiEqtideDistorb(body,update,control,files,module,options,iBody,&iNumMultiProps,&iNumMultiForce);

  VerifyModuleMultiEqtideStellar(body,update,control,files,module,options,iBody,&iNumMultiProps,&iNumMultiForce);

  VerifyModuleMultiBinaryStellar(body,update,control,files,module,options,iBody,&iNumMultiProps,&iNumMultiForce);

  VerifyModuleMultiBinaryEqtideStellar(body,update,control,files,module,options,iBody,&iNumMultiProps,&iNumMultiForce);

  control->iNumMultiProps[iBody] = iNumMultiProps;
  control->iNumMultiForce[iBody] = iNumMultiForce;
  if (control->Io.iVerbose >= VERBALL)
    fprintf(stdout,"All of %s's modules verified.\n",body[iBody].cName);
}

/*
 * Auxiliary Properties for multi-module calculations
 */

void PropsAuxSpinbodyEqtide(BODY *body, EVOLVE *evolve, UPDATE *update, int iBody) {
  // Nothing to see here...

}

void PropsAuxAtmescEqtide(BODY *body,EVOLVE *evolve,UPDATE *update,int iBody) {
  // This function controls how tidal radius is set.

  // If bUseTidalRadius == 0, dTidalRadius <- dRadius
  if(!body[iBody].bUseTidalRadius)
    body[iBody].dTidalRadius = body[iBody].dRadius;
}


void PropsAuxEqtideThermint(BODY *body,EVOLVE *evolve,UPDATE *update,int iBody) {
  /* RB- These first 3 lines were taken from PropsAuxThermint, but
   as they rely on eqtide being called, they belong here.*/
  body[iBody].dK2Man=fdK2Man(body,iBody);
  body[iBody].dImk2Man=fdImk2Man(body,iBody);

  // Include tidal dissapation due to oceans:
  if(body[iBody].bOceanTides)
  {
    body[iBody].dK2 = body[iBody].dK2Man + body[iBody].dK2Ocean;

    // Im(K_2) is weighted sum of mantle and oceam component
    // weighted by the love number of each component
    body[iBody].dImK2 = (body[iBody].dImk2Man + body[iBody].dImK2Ocean);
  }
  // No oceans, thermint dictates ImK2
  else
  {
    body[iBody].dImK2 = body[iBody].dImk2Man;
    body[iBody].dK2 = body[iBody].dK2Man;
  }

  // Sanity checks: enforce upper bound
  if(body[iBody].dK2 > 1.5)
    body[iBody].dK2 = 1.5;

  PropsAuxCPL(body,evolve,update,iBody);
  // Call dTidePowerMan
  body[iBody].dTidalPowMan = fdTidalPowMan(body,iBody);
}

void PropsAuxAtmescEqtideThermint(BODY *body,EVOLVE *evolve,UPDATE *update,int iBody) {
  // Set the mantle parameters first
  body[iBody].dK2Man=fdK2Man(body,iBody);
  body[iBody].dImk2Man=fdImk2Man(body,iBody);

  // If it's the first step, see if it's a runaway greenhouse
  if (evolve->bFirstStep)
  {
    // RG -> no ocean tides
    if(fdInsolation(body, iBody, 0) >= fdHZRG14(body[0].dLuminosity, body[0].dTemperature, body[iBody].dEcc, body[iBody].dMass))
    {
      body[iBody].bOceanTides = 0;
    }
  }

  // Case: No oceans, no envelope
  if(!body[iBody].bOceanTides && !body[iBody].bEnvTides)
  {
    // Mantle controls evolution via thermint
    body[iBody].dImK2 = body[iBody].dImk2Man;
    body[iBody].dK2 = body[iBody].dK2Man;
  }
  // Case: Oceans, no envelope:
  else if(body[iBody].bOceanTides && !body[iBody].bEnvTides)
  {
    // Oceans dominate
    body[iBody].dK2 = body[iBody].dK2Man + body[iBody].dK2Ocean;

    // Im(K_2) is weighted sum of mantle and oceam component
    // weighted by the love number of each component
    body[iBody].dImK2 = (body[iBody].dImk2Man + body[iBody].dImK2Ocean);
  }
  // Case: No oceans, envelope (envelope evap while in runaway):
  else if(!body[iBody].bOceanTides && body[iBody].bEnvTides)
  {
    // Envelope dominates
    body[iBody].dK2 = body[iBody].dK2Man + body[iBody].dK2Env;

    // Im(K_2) is weighted sum of mantle and enevelope component
    // weighted by the love number of each component
    body[iBody].dImK2 = (body[iBody].dImk2Man + body[iBody].dImK2Env);
  }
  // Case: Oceans and evelope->envelope has massive pressure so oceans are super critical (?):
  // Also, envelope and ocean are mutually exclusive so envelope dominates
  else if(body[iBody].bOceanTides && body[iBody].bEnvTides)
  {
    // Envelope and ocean!
    body[iBody].dK2 = body[iBody].dK2Man + body[iBody].dK2Env;

    // Im(K_2) is weighted sum of mantle, envelope and ocean component
    // weighted by the love number of each component
    body[iBody].dImK2 = (body[iBody].dImk2Man + body[iBody].dImK2Env);
  }
  else
    assert(0); // Unknown envelope + ocean behavior

  // Sanity checks: enforce upper bound
  if(body[iBody].dK2 > 1.5)
    body[iBody].dK2 = 1.5;

  // Finally, call EQTIDE props aux then set mantle tidal power
  PropsAuxCPL(body,evolve,update,iBody);
  body[iBody].dTidalPowMan = fdTidalPowMan(body,iBody);

}
/* This does not seem to be necessary
void PropertiesDistOrbDistRot(BODY *body,UPDATE *update,int iBody) {
  body[iBody].dEccSq = body[iBody].dHecc*body[iBody].dHecc + body[iBody].dKecc*body[iBody].dKecc;
}
*/

void PropsAuxRadheatThermint(BODY *body,EVOLVE *evolve,UPDATE *update,int iBody) {
  body[iBody].dRadPowerCore = fdRadPowerCore(update,iBody);
  body[iBody].dRadPowerCrust = fdRadPowerCrust(update,iBody);
  body[iBody].dRadPowerMan = fdRadPowerMan(update,iBody);
}

void PropsAuxEqtideDistorb(BODY *body,EVOLVE *evolve,UPDATE *update,int iBody) {
  body[iBody].dEccSq = body[iBody].dHecc*body[iBody].dHecc + body[iBody].dKecc*body[iBody].dKecc;
}

void PropsAuxEqtideStellar(BODY *body,EVOLVE *evolve,UPDATE *update,int iBody) {
  // In stellar, radius can change depending on model so make sure tidal radius
  // knows that
  body[iBody].dTidalRadius = body[iBody].dRadius;
}

void PropsAuxFlareStellar(BODY *body,EVOLVE *evolve,UPDATE *update,int iBody) {
  SYSTEM system; // dummy for LXUVStellar
  //body[iBody].dLXUV = fdLXUVStellar(body,&system,update,iBody,iBody) + body[iBody].dLXUVFlare;
}

/*
 * Force Behavior for multi-module calculations
 */

void ForceBehaviorEqtideDistOrb(BODY *body,EVOLVE *evolve,IO *io,SYSTEM *system,UPDATE *update,fnUpdateVariable ***fnUpdate,int iFoo,int iBar) {
  if (evolve->iDistOrbModel == RD4) {
    RecalcLaplace(body,evolve,system,io->iVerbose);
    if (body[1].bDistRes) {
      RecalcLaplaceDistRes(body,evolve,system,io->iVerbose);
    }
  } else if (evolve->iDistOrbModel == LL2) {
    RecalcEigenVals(body,evolve,system);
  };
}

void ForceBehaviorEqtideAtmesc(BODY *body,EVOLVE *evolve,IO *io,SYSTEM *system,UPDATE *update,fnUpdateVariable ***fnUpdate,int iFoo,int iBar) {

  int iBody;
  // add print statement
  // output options for benv
  // if benv and denvmass less than dminenvmass, same with oceans, bEnv set initially in verify
  // specify k2rock, gas, ocean,
  // specify tidalqrock, gas, ocean;
  // verify checks

  // there are a few cases we want to account for:
  // 1) env -> ocean -> rock; 2) ocean -> rock; 3) env -> rock
  for (iBody = 1; iBody<=evolve->iNumBodies-1; iBody++) {

    // We think there is an envelope, but there isnt!
    if (body[iBody].bEnv && (body[iBody].dEnvelopeMass <= body[iBody].dMinEnvelopeMass)) {
      fprintf(stderr,"Envelope lost! Changing dTidalQ to:");
      body[iBody].bEnv = 0;

      // is there an ocean? lets set tidalq to that!
      if (body[iBody].bOcean && (body[iBody].dSurfaceWaterMass > body[iBody].dMinSurfaceWaterMass)) {
        fprintf(stderr," dTidalQOcean,\n");
        body[iBody].dTidalQ = body[iBody].dTidalQOcean;
        body[iBody].dK2 = body[iBody].dK2Ocean;
        body[iBody].dImK2 = body[iBody].dImK2Ocean;
      }
      // there is not ocean, so lets use dTidalQRock!
      else {
        fprintf(stderr," dTidalQRock.\n");
        body[iBody].dTidalQ = body[iBody].dTidalQRock;
        body[iBody].dK2 = body[iBody].dK2Rock;
        body[iBody].dImK2 = body[iBody].dImK2Rock;
      }
    }
    // we think theres an ocean, but there isnt!!
    else if (body[iBody].bOcean && (body[iBody].dSurfaceWaterMass <= body[iBody].dMinSurfaceWaterMass)) {
      fprintf(stderr,"Ocean Lost! Switching dTidalQ to: dTidalQRock.\n");
      body[iBody].dTidalQ = body[iBody].dTidalQRock;
      body[iBody].dK2 = body[iBody].dK2Rock;
      body[iBody].dImK2 = body[iBody].dImK2Rock;
    }
  }
}


void ForceBehaviorAtmescEqtideThermint(BODY *body,EVOLVE *evolve,IO *io,SYSTEM *system,UPDATE *update,fnUpdateVariable ***fnUpdate,int iFoo,int iBar) {

  // Loop over non-star bodies
  int iBody;

  // Keeps track of whether or not bOceanTides or bEnvTides were initially set
  // to ensure they don't get turned back on by force behavior
  // If oceans or envelope weren't initially set to be modeled, their Q == -HUGE
  int bOceans = 0;
  int bEnv = 0;

  for(iBody = 1; iBody < evolve->iNumBodies; iBody++)
  {
    // If body 1 is a star (aka using binary), pass
    if(iBody == 1 && body[iBody].bBinary)
      continue;

    // Ocean check
    if(body[iBody].dTidalQOcean < 0)
      bOceans = 0;
    else
      bOceans = 1;

    // Env check
    if(body[iBody].dTidalQEnv < 0)
      bEnv = 0;
    else
      bEnv = 1;

    // Note: With these checks, only do anything if user intended to model them
    // i.e. if bOceanTides == 1 from initial conditions

    // Case: No water -> no ocean tides
    if(bOceans && (body[iBody].dSurfaceWaterMass <= body[iBody].dMinSurfaceWaterMass))
    {
      body[iBody].bOceanTides = 0;
    }
    // Case: Water but it's in the atmosphere: RUNAWAY GREENHOUSE (this is when body actively loses water!)
    else if(bOceans && (body[iBody].dSurfaceWaterMass > body[iBody].dMinSurfaceWaterMass) && body[iBody].bRunaway)
    {
      body[iBody].bOceanTides = 0;
    }
    // Case: Water and on the surface! (this is when body does NOT actively lose water!)
    else if(bOceans && (body[iBody].dSurfaceWaterMass > body[iBody].dMinSurfaceWaterMass) && !body[iBody].bRunaway)
    {
      body[iBody].bOceanTides = 1;
    }

    // Check to see if the envelope is gone: when dEnvelopeMass <= dMinEnvelopeMass
    if(bEnv && (body[iBody].dEnvelopeMass <= body[iBody].dMinEnvelopeMass))
    {
      body[iBody].bEnvTides = 0;
    }
    // Still have the envelope!
    else if(bEnv && (body[iBody].dEnvelopeMass > body[iBody].dMinEnvelopeMass))
    {
      body[iBody].bEnvTides = 1;
    }

    // Enfore that they are mutually exclusive
    // i.e. if using EnvTides or an envelope exists, ocean can't do anything
    if(body[iBody].bEnvTides || (body[iBody].dEnvelopeMass > body[iBody].dMinEnvelopeMass))
      body[iBody].bOceanTides = 0;
  }
}

/*
 *
 * Functions required to add multi-body equations to the matrix
 *
 */

/*! Binary-Eqtide-Stellar semi-major axis derivative set-up*/
void InitializeUpdateEqBinStSemi(BODY *body,UPDATE *update,int iBody) {
  // Only valid if BINARY, EQTIDE, and STELLAR used
  if(body[iBody].bBinary && body[iBody].bStellar && body[iBody].bEqtide && iBody == 1)
  {
    if (update[iBody].iNumSemi == 0)
      update[iBody].iNumVars++;
    update[iBody].iNumSemi++;
  }
}

/*! Binary-Eqtide-Stellar lost energy derivative set-up*/
void InitializeUpdateEqBinStLostEng(BODY *body,UPDATE *update,int iBody) {
  // Only valid if BINARY, EQTIDE, and STELLAR used
  if(body[iBody].bBinary && body[iBody].bStellar && body[iBody].bEqtide && iBody == 1)
  {
    if (update[iBody].iNumLostEng == 0)
      update[iBody].iNumVars++;
    update[iBody].iNumLostEng++;
  }
}


/*! Finalize update (for malloc-ing) for Bin-eq-st semi-major axis derivative */
void FinalizeUpdateMultiEqBinStSemi(BODY *body,UPDATE *update,int *iEqn,int iVar,int iBody,int iFoo, fnUpdateVariable ****fnUpdate) {
  if(body[iBody].bBinary && body[iBody].bStellar && body[iBody].bEqtide && iBody == 1)
  {
    /* Add change in semi-major axis due to BINARY-EQTIDE-STELLAR coupling */
    update[iBody].iaModule[iVar][(*iEqn)] = BINARY + EQTIDE + STELLAR;
    update[iBody].iSemiBinEqSt = (*iEqn);
    (*iEqn)++;
  }
}

/*! Finalize update (for malloc-ing) for Bin-eq-st lost energy derivative */
void FinalizeUpdateMultiEqBinStLostEng(BODY *body,UPDATE *update,int *iEqn,int iVar,int iBody,int iFoo, fnUpdateVariable ****fnUpdate) {
  if(body[iBody].bBinary && body[iBody].bStellar && body[iBody].bEqtide && iBody == 1)
  {
    update[iBody].iaModule[iVar][(*iEqn)] = BINARY + EQTIDE + STELLAR;
    update[iBody].iLostEngBinEqSt = (*iEqn);
    (*iEqn)++;
  }
}

/* GENERAL MULTI-MODULE EQUATION INITIALIZATION/FINALIZATION */

/*!
 * Initialize adding mutli-module equations to the matrix.
 */
void InitializeUpdateMulti(BODY*body,CONTROL *control,MODULE *module,UPDATE *update,fnUpdateVariable ****fnUpdate, int iBody)
{
  // Initialize update struct to accomodate multi-module equations
  InitializeUpdateEqBinStSemi(body,update,iBody);
  InitializeUpdateEqBinStLostEng(body,update,iBody);

  /* More equations here! */
}

/*!
 * Finalize adding mutli-module equations to the matrix.
 */
void FinalizeUpdateMulti(BODY*body,CONTROL *control,MODULE *module,UPDATE *update,fnUpdateVariable ****fnUpdate,int *iVar, int iBody, int iFoo)
{

  int iOtherBody, iEqn;

  // This equation only valid if BINARY, EQTIDE, and STELLAR used for 2nd body
  if (body[iBody].bBinary && body[iBody].bStellar && body[iBody].bEqtide && iBody == 1)
  {

    /* Add change in semi-major axis due to BINARY-EQTIDE-STELLAR coupling */

    // Other star (primary) can also influence this equation
    iOtherBody = 0;

    // Add dSemi-major axis dt from Binary-Eqtide-Stellar coupling to matrix
    update[iBody].iaType[update[iBody].iSemi][update[iBody].iSemiBinEqSt] = 1;
    update[iBody].iNumBodies[update[iBody].iSemi][update[iBody].iSemiBinEqSt] = 2; // Both stars
    update[iBody].iaBody[update[iBody].iSemi][update[iBody].iSemiBinEqSt] = malloc(update[iBody].iNumBodies[update[iBody].iSemi][update[iBody].iSemiBinEqSt]*sizeof(int));
    update[iBody].iaBody[update[iBody].iSemi][update[iBody].iSemiBinEqSt][0] = iBody;
    update[iBody].iaBody[update[iBody].iSemi][update[iBody].iSemiBinEqSt][1] = iOtherBody;
    update[iBody].pdDsemiDtBinEqSt = &update[iBody].daDerivProc[update[iBody].iSemi][update[iBody].iSemiBinEqSt];
    (*fnUpdate)[iBody][update[iBody].iSemi][update[iBody].iSemiBinEqSt] = &fdSemiDtEqBinSt;

    /* Add change in lost energy due to BINARY-EQTIDE-STELLAR coupling */

    // Add dLostEnergy dt from Binary-Eqtide-Stellar coupling to matrix
    update[iBody].iaType[update[iBody].iLostEng][update[iBody].iLostEngBinEqSt] = 1;
    update[iBody].iNumBodies[update[iBody].iLostEng][update[iBody].iLostEngBinEqSt] = 1;
    update[iBody].iaBody[update[iBody].iLostEng][update[iBody].iLostEngBinEqSt] = malloc(update[iBody].iNumBodies[update[iBody].iLostEng][update[iBody].iLostEngBinEqSt]*sizeof(int));
    update[iBody].iaBody[update[iBody].iLostEng][update[iBody].iLostEngBinEqSt][0] = iBody;
    update[iBody].pdDLostEngDtBinEqSt = &update[iBody].daDerivProc[update[iBody].iLostEng][update[iBody].iLostEngBinEqSt];
    (*fnUpdate)[iBody][update[iBody].iLostEng][update[iBody].iLostEngBinEqSt] = &fdLostEngEqBinSt;
  }

/* Add more equations below! */

}
