/**
  @file spinbody.c
  @brief Subroutines that control the integration of the N Body simulation
  @author Hayden Smotherman ([smotherh](https://github.com/smotherh/))

  @date Feb 21 2017
*/

#include "vplanet.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define dot(a,b)        (a[0]*b[0]+a[1]*b[1]+a[2]*b[2])
#define NumElements(x)  (sizeof(x) / sizeof(x[0])) // finds number of elements in an array

void BodyCopySpiNBody(BODY *dest, BODY *src, int iFoo, int iNumBodies,
                      int iBody) {
  int jBody, iGravPerts;
  dest[iBody].dVelX      = src[iBody].dVelX;
  dest[iBody].dVelY      = src[iBody].dVelY;
  dest[iBody].dVelZ      = src[iBody].dVelZ;
  dest[iBody].dPositionX = src[iBody].dPositionX;
  dest[iBody].dPositionY = src[iBody].dPositionY;
  dest[iBody].dPositionZ = src[iBody].dPositionZ;

  dest[iBody].iGravPertsSpiNBody = src[iBody].iGravPertsSpiNBody;

  iGravPerts = src[iBody].iGravPertsSpiNBody;
  for (jBody = 0; jBody < iGravPerts; jBody++) {
    // dest[iBody].dDistance3[jBody]  = src[iBody].dDistance3[jBody];
    dest[iBody].dDistanceX[jBody] = src[iBody].dDistanceX[jBody];
    dest[iBody].dDistanceY[jBody] = src[iBody].dDistanceY[jBody];
    dest[iBody].dDistanceZ[jBody] = src[iBody].dDistanceZ[jBody];
  }
}

void InitializeUpdateTmpBodySpiNBody(BODY *body, CONTROL *control,
                                     UPDATE *update, int iBody) {
  int jBody;
  // This replaces malloc'ing the destination body in BodyCopySpiNBody
  control->Evolve.tmpBody[iBody].dDistance3 =
        malloc(control->Evolve.iNumBodies * sizeof(double));
  control->Evolve.tmpBody[iBody].dDistanceX =
        malloc(control->Evolve.iNumBodies * sizeof(double));
  control->Evolve.tmpBody[iBody].dDistanceY =
        malloc(control->Evolve.iNumBodies * sizeof(double));
  control->Evolve.tmpBody[iBody].dDistanceZ =
        malloc(control->Evolve.iNumBodies * sizeof(double));

  for (jBody = 0; jBody < control->Evolve.iNumBodies; jBody++) {
    // body[iBody].dDistance3[jBody] = 0;
    body[iBody].dDistanceX[jBody] = 0;
    body[iBody].dDistanceY[jBody] = 0;
    body[iBody].dDistanceZ[jBody] = 0;
  }
}

//================================== Read Inputs ===============================
void ReadPositionX(BODY *body, CONTROL *control, FILES *files, OPTIONS *options,
                   SYSTEM *system, int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp = -1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn, options->cName, &dTmp, &lTmp,
                  control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile, options->cName, files->Infile[iFile].cIn, lTmp,
                    control->Io.iVerbose);
    // if (dTmp < 0) //No Negative option right now
    //  body[iFile-1].dPositionX =
    //  dTmp*dNegativeDouble(*options,files->Infile[iFile].cIn,control->Io.iVerbose);
    // else
    body[iFile - 1].dPositionX = dTmp;
    UpdateFoundOption(&files->Infile[iFile], options, lTmp, iFile);
  } else if (iFile > 0) {
    body[iFile - 1].dPositionX = options->dDefault;
  }
}

void ReadPositionY(BODY *body, CONTROL *control, FILES *files, OPTIONS *options,
                   SYSTEM *system, int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp = -1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn, options->cName, &dTmp, &lTmp,
                  control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile, options->cName, files->Infile[iFile].cIn, lTmp,
                    control->Io.iVerbose);
    body[iFile - 1].dPositionY = dTmp;
    UpdateFoundOption(&files->Infile[iFile], options, lTmp, iFile);
  } else if (iFile > 0) {
    body[iFile - 1].dPositionY = options->dDefault;
  }
}

void ReadPositionZ(BODY *body, CONTROL *control, FILES *files, OPTIONS *options,
                   SYSTEM *system, int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp = -1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn, options->cName, &dTmp, &lTmp,
                  control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile, options->cName, files->Infile[iFile].cIn, lTmp,
                    control->Io.iVerbose);
    body[iFile - 1].dPositionZ = dTmp;
    UpdateFoundOption(&files->Infile[iFile], options, lTmp, iFile);
  } else if (iFile > 0) {
    body[iFile - 1].dPositionZ = options->dDefault;
  }
}

void ReadVelX(BODY *body, CONTROL *control, FILES *files, OPTIONS *options,
              SYSTEM *system, int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp = -1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn, options->cName, &dTmp, &lTmp,
                  control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile, options->cName, files->Infile[iFile].cIn, lTmp,
                    control->Io.iVerbose);
    body[iFile - 1].dVelX = dTmp;
    UpdateFoundOption(&files->Infile[iFile], options, lTmp, iFile);
  } else if (iFile > 0) {
    body[iFile - 1].dVelX = options->dDefault;
  }
}

void ReadVelY(BODY *body, CONTROL *control, FILES *files, OPTIONS *options,
              SYSTEM *system, int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp = -1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn, options->cName, &dTmp, &lTmp,
                  control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile, options->cName, files->Infile[iFile].cIn, lTmp,
                    control->Io.iVerbose);
    body[iFile - 1].dVelY = dTmp;
    UpdateFoundOption(&files->Infile[iFile], options, lTmp, iFile);
  } else if (iFile > 0) {
    body[iFile - 1].dVelY = options->dDefault;
  }
}

void ReadVelZ(BODY *body, CONTROL *control, FILES *files, OPTIONS *options,
              SYSTEM *system, int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp = -1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn, options->cName, &dTmp, &lTmp,
                  control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile, options->cName, files->Infile[iFile].cIn, lTmp,
                    control->Io.iVerbose);
    body[iFile - 1].dVelZ = dTmp;
    UpdateFoundOption(&files->Infile[iFile], options, lTmp, iFile);
  } else if (iFile > 0) {
    body[iFile - 1].dVelZ = options->dDefault;
  }
}

void ReadMeanA(BODY *body, CONTROL *control, FILES *files, OPTIONS *options,
               SYSTEM *system, int iFile) {
  /* This parameter cannot exist in the primary file */
  int lTmp = -1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn, options->cName, &dTmp, &lTmp,
                  control->Io.iVerbose);
  if (lTmp >= 0) {
    if (!system->bBarycentric){
    NotPrimaryInput(iFile, options->cName, files->Infile[iFile].cIn, lTmp,
                    control->Io.iVerbose);
    }
    // MeanA can have limited domain when orbit is bound
    // MeanA should have units only in radians if orbit is unbound
    if (body[iFile - 1].dEcc < 1) {                         
      if (control->Units[iFile].iAngle == 0) { 
        if (dTmp < 0 || dTmp > 2 * PI) {
          if (control->Io.iVerbose >= VERBERR) {
            fprintf(stderr, "ERROR: %s must be in the range [0,2*PI].\n",
                    options->cName);
          }
          LineExit(files->Infile[iFile].cIn, lTmp);
        }
        
      } else {
        
        if (dTmp < 0 || dTmp > 360) {
          if (control->Io.iVerbose >= VERBERR) {
            fprintf(stderr, "ERROR: %s must be in the range [0,360].\n",
                    options->cName);
          }
          LineExit(files->Infile[iFile].cIn, lTmp);
        }
        
        /* Change to radians */
        dTmp *= DEGRAD;
      }
    }
    body[iFile - 1].dMeanA = dTmp;
    UpdateFoundOption(&files->Infile[iFile], options, lTmp, iFile);
  } else if (iFile > 0) {
    body[iFile - 1].dMeanA = options->dDefault;
  }
}

void ReadMeanL(BODY *body, CONTROL *control, FILES *files, OPTIONS *options,
               SYSTEM *system, int iFile) {
  /* This parameter cannot exist in the primary file */
  int lTmp = -1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn, options->cName, &dTmp, &lTmp,
                  control->Io.iVerbose);
  if (lTmp >= 0) {
    if (!system->bBarycentric){
    NotPrimaryInput(iFile, options->cName, files->Infile[iFile].cIn, lTmp,
                    control->Io.iVerbose);
    }
    // MeanA can have limited domain when orbit is bound
    // MeanA should have units only in radians if orbit is unbound
    if (body[iFile - 1].dEcc < 1) {                    
      if (control->Units[iFile].iAngle == 0) {
        // Need to move this condition elsewhere. Unbound orbits don't limit MeanL
        
        if (dTmp < 0 || dTmp > 2 * PI) {
          if (control->Io.iVerbose >= VERBERR) {
            fprintf(stderr, "ERROR: %s must be in the range [0,2*PI].\n",
                    options->cName);
          }
          LineExit(files->Infile[iFile].cIn, lTmp);
        }
      } else {
        // Need to move this condition elsewhere. Unbound orbits don't limit MeanL
        if (dTmp < 0 || dTmp > 360) {
          if (control->Io.iVerbose >= VERBERR) {
            fprintf(stderr, "ERROR: %s must be in the range [0,360].\n",
                    options->cName);
          }
          LineExit(files->Infile[iFile].cIn, lTmp);
        }
        /* Change to radians */
        dTmp *= DEGRAD;
      }
    }
    body[iFile - 1].dMeanL = dTmp;
    UpdateFoundOption(&files->Infile[iFile], options, lTmp, iFile);
  } else if (iFile > 0) {
    body[iFile - 1].dMeanL = options->dDefault;
  }
}

void ReadUseOrbParams(BODY *body, CONTROL *control, FILES *files,
                      OPTIONS *options, SYSTEM *system, int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp = -1;
  int bTmp;

  AddOptionBool(files->Infile[iFile].cIn, options->cName, &bTmp, &lTmp,
                control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile, options->cName, files->Infile[iFile].cIn, lTmp,
                    control->Io.iVerbose);
    body[iFile - 1].bUseOrbParams = bTmp;
    UpdateFoundOption(&files->Infile[iFile], options, lTmp, iFile);
  } else {
    body[iFile - 1].bUseOrbParams = options->dDefault;
  }
}

void ReadBarycentric(BODY *body, CONTROL *control, FILES *files,
                      OPTIONS *options, SYSTEM *system, int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp = -1;
  int bTmp = 0;

  AddOptionBool(files->Infile[iFile].cIn, options->cName, &bTmp, &lTmp,
                control->Io.iVerbose);
  if (lTmp >= 0) {
    CheckDuplication(files, options, files->Infile[iFile].cIn, lTmp, VERBALL);
    system->bBarycentric = bTmp;
    UpdateFoundOption(&files->Infile[iFile], options, lTmp, iFile);
  } else if (system->bBarycentric == bTmp) {
    system->bBarycentric = options->dDefault;
  }
}

void InitializeOptionsSpiNBody(OPTIONS *options, fnReadOption fnRead[]) {
  int iOpt, iFile;


  // XXX All of these should be deprecated so that it doesn't matter if the user
  // calls DistOrb or SpiNBody
  sprintf(options[OPT_POSITIONXSPINBODY].cName, "dPositionXSpiNBody");
  sprintf(options[OPT_POSITIONXSPINBODY].cDescr, "X position of the body");
  sprintf(options[OPT_POSITIONXSPINBODY].cDefault, "0");
  sprintf(options[OPT_POSITIONXSPINBODY].cDimension, "length");
  options[OPT_POSITIONXSPINBODY].dDefault   = 0.0;
  options[OPT_POSITIONXSPINBODY].iType      = 2;
  options[OPT_POSITIONXSPINBODY].bMultiFile = 1;
  fnRead[OPT_POSITIONXSPINBODY]             = &ReadPositionX;

  sprintf(options[OPT_POSITIONYSPINBODY].cName, "dPositionYSpiNBody");
  sprintf(options[OPT_POSITIONYSPINBODY].cDescr, "Y position of the body");
  sprintf(options[OPT_POSITIONYSPINBODY].cDefault, "0");
  sprintf(options[OPT_POSITIONYSPINBODY].cDimension, "length");
  options[OPT_POSITIONYSPINBODY].dDefault   = 0.0;
  options[OPT_POSITIONYSPINBODY].iType      = 2;
  options[OPT_POSITIONYSPINBODY].bMultiFile = 1;
  fnRead[OPT_POSITIONYSPINBODY]             = &ReadPositionY;

  sprintf(options[OPT_POSITIONZSPINBODY].cName, "dPositionZSpiNBody");
  sprintf(options[OPT_POSITIONZSPINBODY].cDescr, "Z position of the body");
  sprintf(options[OPT_POSITIONZSPINBODY].cDefault, "0");
  sprintf(options[OPT_POSITIONZSPINBODY].cDimension, "length");
  options[OPT_POSITIONZSPINBODY].dDefault   = 0.0;
  options[OPT_POSITIONZSPINBODY].iType      = 2;
  options[OPT_POSITIONZSPINBODY].bMultiFile = 1;
  fnRead[OPT_POSITIONZSPINBODY]             = &ReadPositionZ;

  sprintf(options[OPT_VELXSPINBODY].cName, "dVelXSpiNBody");
  sprintf(options[OPT_VELXSPINBODY].cDescr, "X velocity of the body");
  sprintf(options[OPT_VELXSPINBODY].cDefault, "0");
  sprintf(options[OPT_VELXSPINBODY].cDimension, "length/time");
  options[OPT_VELXSPINBODY].dDefault   = 0.0;
  options[OPT_VELXSPINBODY].iType      = 2;
  options[OPT_VELXSPINBODY].bMultiFile = 1;
  fnRead[OPT_VELXSPINBODY]             = &ReadVelX;

  sprintf(options[OPT_VELYSPINBODY].cName, "dVelYSpiNBody");
  sprintf(options[OPT_VELYSPINBODY].cDescr, "Y velocity of the body");
  sprintf(options[OPT_VELYSPINBODY].cDefault, "0");
  sprintf(options[OPT_VELYSPINBODY].cDimension, "length/time");
  options[OPT_VELYSPINBODY].dDefault   = 0.0;
  options[OPT_VELYSPINBODY].iType      = 2;
  options[OPT_VELYSPINBODY].bMultiFile = 1;
  fnRead[OPT_VELYSPINBODY]             = &ReadVelY;

  sprintf(options[OPT_VELZSPINBODY].cName, "dVelZSpiNBody");
  sprintf(options[OPT_VELZSPINBODY].cDescr, "Z velocity of the body");
  sprintf(options[OPT_VELZSPINBODY].cDefault, "0");
  sprintf(options[OPT_VELZSPINBODY].cDimension, "length/time");
  options[OPT_VELZSPINBODY].dDefault   = 0.0;
  options[OPT_VELZSPINBODY].iType      = 2;
  options[OPT_VELZSPINBODY].bMultiFile = 1;
  fnRead[OPT_VELZSPINBODY]             = &ReadVelZ;

  sprintf(options[OPT_MEANA].cName, "dMeanA");
  sprintf(options[OPT_MEANA].cDescr, "Mean anomaly");
  sprintf(options[OPT_MEANA].cDefault, "0.0");
  sprintf(options[OPT_MEANA].cDimension, "angle");
  options[OPT_MEANA].dDefault   = 0.0;
  options[OPT_MEANA].iType      = 2;
  options[OPT_MEANA].bMultiFile = 1;
  fnRead[OPT_MEANA]             = &ReadMeanA;

  sprintf(options[OPT_MEANL].cName, "dMeanL");
  sprintf(options[OPT_MEANL].cDescr, "Mean longitude");
  sprintf(options[OPT_MEANL].cDefault, "0.0");
  sprintf(options[OPT_MEANL].cDimension, "angle");
  options[OPT_MEANL].dDefault   = 0.0;
  options[OPT_MEANL].iType      = 2;
  options[OPT_MEANL].bMultiFile = 1;
  fnRead[OPT_MEANL]             = &ReadMeanL;

  sprintf(options[OPT_USEORBPARAMS].cName, "bUseOrbParams");
  sprintf(options[OPT_USEORBPARAMS].cDescr,
          "Flag to use orbital parameters as inputs");
  sprintf(options[OPT_USEORBPARAMS].cDefault, "0");
  options[OPT_USEORBPARAMS].dDefault   = 0;
  options[OPT_USEORBPARAMS].iType      = 0;
  options[OPT_USEORBPARAMS].bMultiFile = 1;
  fnRead[OPT_USEORBPARAMS]             = &ReadUseOrbParams;

  sprintf(options[OPT_BARYCENTRIC].cName, "bBarycentric");
  sprintf(options[OPT_BARYCENTRIC].cDescr, "Coordinate system's origin at the barycenter");
  sprintf(options[OPT_BARYCENTRIC].cDefault, "0");
  options[OPT_BARYCENTRIC].dDefault = 0;
  options[OPT_BARYCENTRIC].iType = 0;
  options[OPT_BARYCENTRIC].bMultiFile = 0;
  options[OPT_BARYCENTRIC].bNeg = 0;
  options[OPT_BARYCENTRIC].iFileType = 2;
  options[OPT_BARYCENTRIC].iModuleBit = SPINBODY;
  fnRead[OPT_BARYCENTRIC]             = &ReadBarycentric;
}

void ReadOptionsSpiNBody(BODY *body, CONTROL *control, FILES *files,
                         OPTIONS *options, SYSTEM *system,
                         fnReadOption fnRead[], int iBody) {
  int iOpt;

  for (iOpt = OPTSTARTSPINBODY; iOpt < OPTENDSPINBODY; iOpt++) {
    if (options[iOpt].iType != -1) {
      fnRead[iOpt](body, control, files, &options[iOpt], system, iBody + 1);
    }
  }
}

//============================ End Read Inputs =================================

void InitializeBodySpiNBody(BODY *body, CONTROL *control, UPDATE *update,
                            int iBody, int iModule) {
  int iTmpBody = 0, jBody;
  if (body[iBody].bSpiNBody) {
    body[iBody].iGravPertsSpiNBody =
          control->Evolve
                .iNumBodies; // All bodies except the body itself are perturbers
    // body[iBody].dDistance3 =
    // malloc(control->Evolve.iNumBodies*sizeof(double));
    body[iBody].dDistanceX =
          malloc(control->Evolve.iNumBodies * sizeof(double));
    body[iBody].dDistanceY =
          malloc(control->Evolve.iNumBodies * sizeof(double));
    body[iBody].dDistanceZ =
          malloc(control->Evolve.iNumBodies * sizeof(double));

    for (jBody = 0; jBody < control->Evolve.iNumBodies; jBody++) {
      // body[iBody].dDistance3[jBody] = 0;
      body[iBody].dDistanceX[jBody] = 0;
      body[iBody].dDistanceY[jBody] = 0;
      body[iBody].dDistanceZ[jBody] = 0;
    }

    //All of this should be moved to verifyspinbody or deleted


    // If orbital parameters are defined, then we want to set position and
    // velocity based on those
    if (body[iBody].bUseOrbParams) {
      if (iBody == 0) { // Only want to do this once
        for (iTmpBody = 0; iTmpBody < control->Evolve.iNumBodies; iTmpBody++) {
          if (iTmpBody != 0) {
            body[iTmpBody].dMu = BIGG * (body[0].dMass + body[iTmpBody].dMass);
          } else {
            body[iTmpBody].dMu = 0;
          }
          // Convert all bodies w/ orbital elements to Heliocentric
          if (body[iTmpBody].bUseOrbParams) {
            body[iTmpBody].dSinc = sin(0.5 * body[iTmpBody].dInc);
            body[iTmpBody].dPinc =
                  body[iTmpBody].dSinc * sin(body[iTmpBody].dLongA);
            body[iTmpBody].dQinc =
                  body[iTmpBody].dSinc * cos(body[iTmpBody].dLongA);
            body[iTmpBody].dHecc =
                  body[iTmpBody].dEcc * sin(body[iTmpBody].dLongP);
            body[iTmpBody].dKecc =
                  body[iTmpBody].dEcc * cos(body[iTmpBody].dLongP);
            //fvOrbElems2HelioCart(body, iTmpBody);
          }
        }
      }

      //fvHelioCart2BaryCart(body, control->Evolve.iNumBodies, iBody);
      /*
      body[iBody].dPositionX = body[iBody].dBCartPos[0];
      body[iBody].dPositionY = body[iBody].dBCartPos[1];
      body[iBody].dPositionZ = body[iBody].dBCartPos[2];
      body[iBody].dVelX      = body[iBody].dBCartVel[0];
      body[iBody].dVelY      = body[iBody].dBCartVel[1];
      body[iBody].dVelZ      = body[iBody].dBCartVel[2];
      */

    }
  }
}

void InitializeUpdateSpiNBody(BODY *body, UPDATE *update, int iBody) {
  if (iBody >= 0) {
    if (update[iBody].iNumPositionX == 0) {
      update[iBody].iNumVars++;
    }
    update[iBody].iNumPositionX++;

    if (update[iBody].iNumPositionY == 0) {
      update[iBody].iNumVars++;
    }
    update[iBody].iNumPositionY++;

    if (update[iBody].iNumPositionZ == 0) {
      update[iBody].iNumVars++;
    }
    update[iBody].iNumPositionZ++;

    if (update[iBody].iNumVelX == 0) {
      update[iBody].iNumVars++;
    }
    update[iBody].iNumVelX++;

    if (update[iBody].iNumVelY == 0) {
      update[iBody].iNumVars++;
    }
    update[iBody].iNumVelY++;

    if (update[iBody].iNumVelZ == 0) {
      update[iBody].iNumVars++;
    }
    update[iBody].iNumVelZ++;
  }
}

//======================== Verify Variable Functions ===========================
void VerifyPositionX(BODY *body, OPTIONS *options, UPDATE *update, double dAge,
                     int iBody) {

  update[iBody].iaType[update[iBody].iPositionX][0]     = 7;
  update[iBody].iNumBodies[update[iBody].iPositionX][0] = 1;
  update[iBody].iaBody[update[iBody].iPositionX][0]     = malloc(
            update[iBody].iNumBodies[update[iBody].iPositionX][0] * sizeof(int));
  update[iBody].iaBody[update[iBody].iPositionX][0][0] = iBody;

  update[iBody].pdDPositionX =
        &update[iBody].daDerivProc[update[iBody].iPositionX][0];
}

void VerifyPositionY(BODY *body, OPTIONS *options, UPDATE *update, double dAge,
                     int iBody) {

  update[iBody].iaType[update[iBody].iPositionY][0]     = 7;
  update[iBody].iNumBodies[update[iBody].iPositionY][0] = 1;
  update[iBody].iaBody[update[iBody].iPositionY][0]     = malloc(
            update[iBody].iNumBodies[update[iBody].iPositionY][0] * sizeof(int));
  update[iBody].iaBody[update[iBody].iPositionY][0][0] = iBody;

  update[iBody].pdDPositionY =
        &update[iBody].daDerivProc[update[iBody].iPositionY][0];
}

void VerifyPositionZ(BODY *body, OPTIONS *options, UPDATE *update, double dAge,
                     int iBody) {

  update[iBody].iaType[update[iBody].iPositionZ][0]     = 7;
  update[iBody].iNumBodies[update[iBody].iPositionZ][0] = 1;
  update[iBody].iaBody[update[iBody].iPositionZ][0]     = malloc(
            update[iBody].iNumBodies[update[iBody].iPositionZ][0] * sizeof(int));
  update[iBody].iaBody[update[iBody].iPositionZ][0][0] = iBody;

  update[iBody].pdDPositionZ =
        &update[iBody].daDerivProc[update[iBody].iPositionZ][0];
}

void VerifyVelX(BODY *body, OPTIONS *options, UPDATE *update, double dAge,
                int iBody) {

  update[iBody].iaType[update[iBody].iVelX][0]     = 7;
  update[iBody].iNumBodies[update[iBody].iVelX][0] = 1;
  update[iBody].iaBody[update[iBody].iVelX][0] =
        malloc(update[iBody].iNumBodies[update[iBody].iVelX][0] * sizeof(int));
  update[iBody].iaBody[update[iBody].iVelX][0][0] = iBody;

  update[iBody].pdDVelX = &update[iBody].daDerivProc[update[iBody].iVelX][0];
}

void VerifyVelY(BODY *body, OPTIONS *options, UPDATE *update, double dAge,
                int iBody) {

  update[iBody].iaType[update[iBody].iVelY][0]     = 7;
  update[iBody].iNumBodies[update[iBody].iVelY][0] = 1;
  update[iBody].iaBody[update[iBody].iVelY][0] =
        malloc(update[iBody].iNumBodies[update[iBody].iVelY][0] * sizeof(int));
  update[iBody].iaBody[update[iBody].iVelY][0][0] = iBody;

  update[iBody].pdDVelY = &update[iBody].daDerivProc[update[iBody].iVelY][0];
}

void VerifyVelZ(BODY *body, OPTIONS *options, UPDATE *update, double dAge,
                int iBody) {

  update[iBody].iaType[update[iBody].iVelZ][0]     = 7;
  update[iBody].iNumBodies[update[iBody].iVelZ][0] = 1;
  update[iBody].iaBody[update[iBody].iVelZ][0] =
        malloc(update[iBody].iNumBodies[update[iBody].iVelZ][0] * sizeof(int));
  update[iBody].iaBody[update[iBody].iVelZ][0][0] = iBody;

  update[iBody].pdDVelZ = &update[iBody].daDerivProc[update[iBody].iVelZ][0];
}

void VerifyGM(BODY *body, CONTROL *control) {
  int iBody;

  for (iBody = 0; iBody < control->Evolve.iNumBodies; iBody++) {
    body[iBody].dGM = BIGG * body[iBody].dMass;
  }
}

void AssignSpiNBodyDerivatives(BODY *body, EVOLVE *evolve, UPDATE *update,
                               fnUpdateVariable ***fnUpdate, int iBody) {
  fnUpdate[iBody][update[iBody].iPositionX][0] = &fdDPositionXDt;
  fnUpdate[iBody][update[iBody].iPositionY][0] = &fdDPositionYDt;
  fnUpdate[iBody][update[iBody].iPositionZ][0] = &fdDPositionZDt;
  fnUpdate[iBody][update[iBody].iVelX][0]      = &fdDVelXDt;
  fnUpdate[iBody][update[iBody].iVelY][0]      = &fdDVelYDt;
  fnUpdate[iBody][update[iBody].iVelZ][0]      = &fdDVelZDt;
}

void NullSpiNBodyDerivatives(BODY *body, EVOLVE *evolve, UPDATE *update,
                             fnUpdateVariable ***fnUpdate, int iBody) {
  fnUpdate[iBody][update[iBody].iPositionX][0] = &fndUpdateFunctionTiny;
  fnUpdate[iBody][update[iBody].iPositionY][0] = &fndUpdateFunctionTiny;
  fnUpdate[iBody][update[iBody].iPositionZ][0] = &fndUpdateFunctionTiny;
  fnUpdate[iBody][update[iBody].iVelX][0]      = &fndUpdateFunctionTiny;
  fnUpdate[iBody][update[iBody].iVelY][0]      = &fndUpdateFunctionTiny;
  fnUpdate[iBody][update[iBody].iVelZ][0]      = &fndUpdateFunctionTiny;
}

void fvAssignHelioOrbElems(BODY *body, int iBody) {
    body[iBody].dHelioSemi = body[iBody].dSemi;
    body[iBody].dHelioEcc = body[iBody].dEcc;
    body[iBody].dHelioInc = body[iBody].dInc;
    body[iBody].dHelioArgP = body[iBody].dArgP;
    body[iBody].dHelioLongA = body[iBody].dLongA;
    body[iBody].dHelioLongP = body[iBody].dLongP;
    body[iBody].dHelioMeanA = body[iBody].dMeanA;
    body[iBody].dHelioMeanL =  body[iBody].dMeanL;
}

void fvAssignBaryOrbElems(BODY *body, SYSTEM *system, int iBody){
  if (system->bBarycentric) {
    body[iBody].dBarySemi = body[iBody].dSemi;
    body[iBody].dBaryEcc = body[iBody].dEcc;
    body[iBody].dBaryInc = body[iBody].dInc;
    body[iBody].dBaryArgP = body[iBody].dArgP;
    body[iBody].dBaryLongA = body[iBody].dLongA;
    body[iBody].dBaryLongP = body[iBody].dLongP;
    body[iBody].dBaryMeanA = body[iBody].dMeanA;
    body[iBody].dBaryMeanL = body[iBody].dMeanL;
  }
}

void fvAssignCartOutputs2BaryCart(BODY *body, int iBody) {
  body[iBody].dPositionX = body[iBody].dBCartPos[0];
  body[iBody].dPositionY = body[iBody].dBCartPos[1];
  body[iBody].dPositionZ = body[iBody].dBCartPos[2];

  body[iBody].dVelX = body[iBody].dBCartVel[0];
  body[iBody].dVelY = body[iBody].dBCartVel[1];
  body[iBody].dVelZ = body[iBody].dBCartVel[2];
}

void fvMoveOptions2Helio(BODY *body, int iBody) {
  /*
  When activating HelioCart, dPosition and dVel arrays are temporarily defined as HelioCart
  since the user meant to define these variables in HelioCart initially.
  They shortly get redefined to BaryCart after BaryCart values are calculated.
  */
  body[iBody].dHCartPos[0] = body[iBody].dPositionX;
  body[iBody].dHCartPos[1] = body[iBody].dPositionY;
  body[iBody].dHCartPos[2] = body[iBody].dPositionZ;

  body[iBody].dHCartVel[0] = body[iBody].dVelX;
  body[iBody].dHCartVel[1] = body[iBody].dVelY;
  body[iBody].dHCartVel[2] = body[iBody].dVelZ;
}

void fvAssignBaryCart(BODY *body, int iBody) {
  body[iBody].dBCartPos[0] = body[iBody].dPositionX;
  body[iBody].dBCartPos[1] = body[iBody].dPositionY;
  body[iBody].dBCartPos[2] = body[iBody].dPositionZ;

  body[iBody].dBCartVel[0] = body[iBody].dVelX;
  body[iBody].dBCartVel[1] = body[iBody].dVelY;
  body[iBody].dBCartVel[2] = body[iBody].dVelZ;
}

void fvAssignBaryCart2BaryCart(BODY *body, int iBody) {
  /*
  I didn't know what else to call this function, but we assign 
  these functions below if we want BaryCart outputs
  */
  body[iBody].dBaryPosX = body[iBody].dBCartPos[0];
  body[iBody].dBaryPosY = body[iBody].dBCartPos[1];
  body[iBody].dBaryPosZ = body[iBody].dBCartPos[2];

  body[iBody].dBaryVelX = body[iBody].dBCartVel[0];
  body[iBody].dBaryVelY = body[iBody].dBCartVel[1];
  body[iBody].dBaryVelZ = body[iBody].dBCartVel[2];
}

void fvAssignBaryCart2HelioCart(BODY *body, int iBody) {
  body[iBody].dHelioPosX = body[iBody].dHCartPos[0];
  body[iBody].dHelioPosY = body[iBody].dHCartPos[1];
  body[iBody].dHelioPosZ = body[iBody].dHCartPos[2];

  body[iBody].dHelioVelX = body[iBody].dHCartVel[0];
  body[iBody].dHelioVelY = body[iBody].dHCartVel[1];
  body[iBody].dHelioVelZ = body[iBody].dHCartVel[2];
}

void AssignAllCoords(BODY *body, CONTROL *control, FILES *files, SYSTEM *system, int iBody) {
  //VerifyOutputCoords(body, files, output, iBody);
  if (!body[iBody].bUseOrbParams) { // If input was BaryCart or HelioCart
    fvAssignBaryCart(body, iBody); // We assign the vectors named dBCart to the input values
  }
  double iNumBodies = control->Evolve.iNumBodies;
  // Need Gravitational Parameter to be assigned
  // Use BaryMu because iterated coordinates are Barycentric
  body[iBody].dMu = BarycentricMu(body, iNumBodies, iBody);
  // Do a check if orbelems need to be converted to inv_plane
  // inv_plane only accepts barycart coords
  if (files->Outfile[iBody].iOutputCoordBit & HELIOCART) {
    fvBaryCart2HelioCart(body, iBody);
    fvAssignBaryCart2HelioCart(body, iBody);
  }
  if (files->Outfile[iBody].iOutputCoordBit & HELIOELEMS) {
    fvBaryCart2HelioOrbElems(body, iNumBodies, iBody);
    fvAssignHelioOrbElems(body, iBody);
  }
  if (files->Outfile[iBody].iOutputCoordBit & BARYELEMS) {
    fvBaryCart2BaryOrbElems(body, iNumBodies, iBody);
    //fvAssignBaryOrbElems(body, system, iBody);
  }
}

void VerifyInputCoords(BODY *body, CONTROL *control, OPTIONS *options, SYSTEM *system, int iBody) {
  // Allocate dHCartPos, dBCartPos, dHCartVel, dBCartVel
  // We only want to allocate all of the positions and velocities for every body, so we do this one time at iBody = 0;
  if (iBody == 0) {
    int iTmpBody = 0;
    for (iTmpBody = 0; iTmpBody < control->Evolve.iNumBodies; iTmpBody++){
      body[iTmpBody].dBCartPos = malloc(3 * sizeof(double));
      body[iTmpBody].dBCartVel = malloc(3 * sizeof(double));
      body[iTmpBody].dHCartPos = malloc(3 * sizeof(double));
      body[iTmpBody].dHCartVel = malloc(3 * sizeof(double));
    }
  }


  if (body[iBody].bUseOrbParams) {  
    if(!system->bBarycentric) {
      printf("HelioOrbElems. Converting to HelioCart...\n");
      if (iBody == 0) {
        int iTmpBody = 0;
        for (iTmpBody = 0; iTmpBody < control->Evolve.iNumBodies; iTmpBody++) {
          fvAssignHelioOrbElems(body, iTmpBody);
          if (iTmpBody > 0) { // The central body already has all OrbElems as zero.
            VerifyAltOrbElems(body, options, iTmpBody);
          }
          fvHelioOrbElems2HelioCart(body, control->Evolve.iNumBodies, iTmpBody);
        }
      } 
      fvHelioCart2BaryCart(body, control->Evolve.iNumBodies, iBody);
      // fvAssignSpinBodyVariables();
    } else {
      printf("BaryOrbElems. Converting to BaryCart...\n");
      fvAssignBaryOrbElems(body, system, iBody);
      VerifyAltOrbElems(body, options, iBody);
      fvBaryOrbElems2BaryCart(body, control->Evolve.iNumBodies, iBody);
    } fvAssignCartOutputs2BaryCart(body, iBody); // Example: dPositionX = dBCartPos[0];
  } else {
    if(!system->bBarycentric) {
      printf("HelioCart. Converting to BaryCart...\n");
      // dPos variables get reassigned later as BaryCart values. Only use fvMoveOptions2Helio initially
      if (body[iBody].dPositionX == 0 && body[iBody].dPositionY == 0 && body[iBody].dPositionZ == 0) {
        int iTmpBody = 0;
        for (iTmpBody = 0; iTmpBody < control->Evolve.iNumBodies; iTmpBody++) {
          fvMoveOptions2Helio(body, iTmpBody);  // Example: dHCartPos[0] = dPositionX;
        }
      }
      fvHelioCart2BaryCart(body, control->Evolve.iNumBodies, iBody);
      fvAssignCartOutputs2BaryCart(body, iBody);
      // fvAssignSpinBodyVariables();
    } else {
      // BaryCart was the input. No conversions occurred, so we need to assign BaryCart Pos/Vel to dPosition/dVel
      fvAssignBaryCart(body, iBody); // Example: dBCartPos[0] = dPositionX;
    }
    printf("BaryCart. No Conversion needed.\n");
  }
  // At this point dPosition and dVelocity are in BaryCart coordinates
}

void VerifyOutputCoords(BODY *body, FILES *files, OUTPUT *output, int iBody) {
  int iCol, iValue; // for loop indices  
  // Arrays that identify the output variables
  int iBARYCART_Outputs[6] = {OUT_BARYPOSX, OUT_BARYPOSY, OUT_BARYPOSZ, 
                            OUT_BARYVELX, OUT_BARYVELY, OUT_BARYVELZ};

  int iHELIOCART_Outputs[6] = {OUT_HELIOPOSX, OUT_HELIOPOSY, OUT_HELIOPOSZ, 
                            OUT_HELIOVELX, OUT_HELIOVELY, OUT_HELIOVELZ};

  int iHELIOELEMS_Outputs[10] = {OUT_HELIOSEMI, OUT_HELIOECC, OUT_HELIOINC, OUT_HELIOLONGP,
                            OUT_HELIOLONGA, OUT_HELIOARGP, OUT_HELIOMEANA, OUT_HELIOMEANL,
                            OUT_HELIOECCA, OUT_HELIOHYPA};

  int iBARYELEMS_Outputs[15] = {OUT_BARYSEMI, OUT_BARYECC, OUT_BARYINC, OUT_BARYLONGP,
                            OUT_BARYLONGA, OUT_BARYARGP, OUT_BARYMEANA, OUT_BARYMEANL,
                            OUT_BARYECCA, OUT_BARYHYPA, OUT_BARYMU, OUT_BARYECCSQ, 
                            OUT_BARYMEANMOTION, OUT_BARYORBPERIOD, OUT_BARYSINC};
  // Should be defined as something before being summed
  files->Outfile[iBody].iOutputCoordBit = 1; // Identifies output variable's coordinates 
  
  // for loops find variables in the .in files
  for (iCol = 0;  iCol < files->Outfile[iBody].iNumCols; iCol++) {
    for (iValue = 0; iValue < NumElements(iBARYCART_Outputs); iValue++) {
      if (memcmp(files->Outfile[iBody].caCol[iCol], output[iBARYCART_Outputs[iValue]].cName,
                        strlen(output[iBARYCART_Outputs[iValue]].cName)) == 0) {
          files->Outfile[iBody].iOutputCoordBit += BARYCART; // BARYCART output found
          iCol = files->Outfile[iBody].iNumCols; // breaks out of nested for loop
          break;                          
      }
    }
  }
  for (iCol = 0;  iCol < files->Outfile[iBody].iNumCols; iCol++) {
    for (iValue = 0; iValue < NumElements(iHELIOCART_Outputs); iValue++) {
      if (memcmp(files->Outfile[iBody].caCol[iCol], output[iHELIOCART_Outputs[iValue]].cName,
                        strlen(output[iHELIOCART_Outputs[iValue]].cName)) == 0) {
          files->Outfile[iBody].iOutputCoordBit += HELIOCART; // HELIOCART output found
          iCol = files->Outfile[iBody].iNumCols; // breaks out of nested for loop
          break;                          
      }
    }
  }
  for (iCol = 0;  iCol < files->Outfile[iBody].iNumCols; iCol++) {
    for (iValue = 0; iValue < NumElements(iHELIOELEMS_Outputs); iValue++) {
      if (memcmp(files->Outfile[iBody].caCol[iCol], output[iHELIOELEMS_Outputs[iValue]].cName,
                        strlen(output[iHELIOELEMS_Outputs[iValue]].cName)) == 0) {
          files->Outfile[iBody].iOutputCoordBit += HELIOELEMS; // HELIOELEMS output found
          iCol = files->Outfile[iBody].iNumCols; // breaks out of nested for loop
          break;                          
      }
    }
  }
  for (iCol = 0;  iCol < files->Outfile[iBody].iNumCols; iCol++) {
    for (iValue = 0; iValue < NumElements(iBARYELEMS_Outputs); iValue++) {
      if (memcmp(files->Outfile[iBody].caCol[iCol], output[iBARYELEMS_Outputs[iValue]].cName,
                        strlen(output[iBARYELEMS_Outputs[iValue]].cName)) == 0) {
          files->Outfile[iBody].iOutputCoordBit += BARYELEMS; // BARYELEMS output found
          iCol = files->Outfile[iBody].iNumCols; // breaks out of nested for loop
          break;                          
      }
    }
  }
}

void CoordinateMessage(BODY *body, CONTROL *control, int iBody, char *cMessage) {
  if (iBody == control->Evolve.iNumBodies - 1){
        printf(cMessage);
      }
}

void VerifySpiNBody(BODY *body, CONTROL *control, FILES *files,
                    OPTIONS *options, OUTPUT *output, SYSTEM *system,
                    UPDATE *update, int iBody, int iModule) {
  




  VerifyVelX(body, options, update, body[iBody].dAge, iBody);
  VerifyVelY(body, options, update, body[iBody].dAge, iBody);
  VerifyVelZ(body, options, update, body[iBody].dAge, iBody);
  VerifyPositionX(body, options, update, body[iBody].dAge, iBody);
  VerifyPositionY(body, options, update, body[iBody].dAge, iBody);
  VerifyPositionZ(body, options, update, body[iBody].dAge, iBody);


  VerifyInputCoords(body, control, options, system, iBody);
  VerifyOutputCoords(body, files, output, iBody);

  // VerifyGM(body,control);

  control->fnForceBehavior[iBody][iModule]   = &fnForceBehaviorSpiNBody;
  control->fnPropsAux[iBody][iModule]        = &PropsAuxSpiNBody;
  control->Evolve.fnBodyCopy[iBody][iModule] = &BodyCopySpiNBody;

   
  if (system->bBarycentric) {
    //if (iBody == control->Evolve.iNumBodies - 1){
    //  printf("Using barycentric coordinates.\n");
    //}
    CoordinateMessage(body, control, iBody, "Using barycentric coordinates.\n");
    if (body[iBody].bUseOrbParams) {
      printf("Using orbital elements.\n"); // INSIDE BARYELEMS
      //fvBaryCart2BaryOrbElems(body, control->Evolve.iNumBodies, iBody);
    } else {
      printf("Using Cartesian coordinates.\n"); // INSIDE BARYCART
      

    }  
  } else {
    printf("Using heliocentric coordinates.\n");
    //fvBaryCart2HelioCart(body, iBody);
    //fvAssignBaryCart2HelioCart(body, iBody);
    if (body[iBody].bUseOrbParams) {
      printf("Using orbital elements.\n"); // INSIDE HELIOELEMS
      //convertHelioElems2BaryCart(body, control, system);
    } else {
      int jBody = 0;
      for (jBody = 0; jBody < control->Evolve.iNumBodies; jBody++) {
        //fvHelioCart2BaryCart(body, control->Evolve.iNumBodies, jBody);
      }
      printf("Using Cartesian coordinates.\n"); // INSIDE HELIOCART
      //convertHelioCart2BaryCart(body, control, system);
    }
  }

}

//========================== End Verify Functions ==============================

//========================== Start Halt Functions ==============================

/**
  Check the maximum allowed mutual inclination.

@param body A pointer to the current BODY instance
@param control A pointer to the integration CONTROL instance
@param files A pointer to the array of input FILES
@param options A pointer to the OPTIONS instance
@param system A pointer to the SYSTEM instance
@param iFile The current file number

@return TRUE if one mutual incliantion in a system is larger than
  dHaltMaxMutualInc, FALSE if not
*/
int fbHaltMaxMutualIncSpiNBody(BODY *body, EVOLVE *evolve, HALT *halt, IO *io,
                               UPDATE *update, fnUpdateVariable ***fnUpdate,
                               int iBody) {

  int jBody;

  // Calculate orbital elements
  for (iBody = 0; iBody < evolve->iNumBodies; iBody++) {
    cart2osc(body, iBody);
  }

  for (iBody = 0; iBody < evolve->iNumBodies; iBody++) {
    for (jBody = iBody + 1; jBody < evolve->iNumBodies; jBody++) {
      // 0 is to check for halt, not progress
      if (fbCheckMaxMutualInc(body, evolve, halt, io, iBody, jBody, 0)) {
        return 1;
      }
    }
  }

  return 0;
}

//========================== Start Halt Functions ==============================

//========================== Coordinate Changes ================================

double LimitRounding(double x) {
  /* 
  Machine precision can round inaccurate values that eventually become present
  the more calculations vplanet makes. 
  */
  if (x < 1e-16) {
    x = 0.0;
  }
  return x;
}

//fmodPos() restricts inputs of Orbital Element in the domain [0, 2*PI)
double fmodPos(double x, double y) { //returns modulo_{y}(x) remaining in the domain 0 <= x < y
  double result;
  result = fmod(x, y);
  while (result < 0.0) {
    result += y;
  }
  return result;
}

double TotalMass(BODY *body, int iNumBodies) {
  double dTmpTotalMass = 0.0;
  for (int iTmpBody = 0; iTmpBody < iNumBodies; iTmpBody++) {
    dTmpTotalMass += body[iTmpBody].dMass;
  }
  return dTmpTotalMass;
}

double BarycentricMu(BODY *body, int iNumBodies, int iBody) {
  double mTotal, dBaryMu; 
  mTotal = TotalMass(body, iNumBodies);
  dBaryMu = mTotal * cube(1. - body[iBody].dMass / mTotal);
  return dBaryMu;
}

void OrbElems2Cart(ELEMS elems, double *dPos, double *dVel) {
  double dCosi, dSini, dCosLongA, dSinLongA, dCosArgP, dSinArgP, dEccA, dCosEccA, dSinEccA,
            dHypA, dCoshHypA, dSinhHypA, dL1, dM1, dN1, dL2, dM2, dN2, dSemi, dEcc, 
            dMu, mTotal, dBaryRelation, dXi, dEta, dVelScl;
  // Note: Improved work can be made by introducing parabolic orbits.
  /*
  Most of the if statements below were made in consequence of the machine 
  precision errors present. If a future developer fixes these tiny errors,
  then the if statements would not be necessary.
  */
  if (elems.dInc == 0.0) {
    dCosi = 1.0;
    dSini = 0.0;

    dCosLongA = 1.0;
    dSinLongA = 0.0;
  } else {
    dCosi = cos(elems.dInc);
    dSini = sin(elems.dInc);

    dCosLongA = cos(elems.dLongA);
    dSinLongA = sin(elems.dLongA);
  }
  if (elems.dArgP == PI) { // want values to be exact for dBaryArgP = 180 deg
    dCosArgP = -1.0;
    dSinArgP = 0.0;
  } else {
    dCosArgP = cos(elems.dArgP);
    dSinArgP = sin(elems.dArgP);
  }

  dSemi = elems.dSemi;
  dEcc = elems.dEcc;
  dCosi = LimitRounding(dCosi);
  dSini = LimitRounding(dSini);
  dCosLongA = LimitRounding(dCosLongA);
  dSinLongA = LimitRounding(dSinLongA);
  dCosArgP = LimitRounding(dCosArgP);
  dSinArgP = LimitRounding(dSinArgP);
  if (dEcc > 1) {
    // By convention the semi-major axis is negative in unbound orbits
    dSemi = -dSemi;
  }

  //Temporarily defining dBaryMu as the Heliocentric Mu. Will change this line later.
  //body[iBody].dBaryMu = BIGG*(body[0].dMass + body[iBody].dMass);
  //dMu = body[iBody].dBaryMu;
  /* UPDATE:
  Could not continue using Heliocentric mu because BaryVel[i] becomes too big,
  causing body[1] to escape its orbit and crashes vplanet. Resorting to the BaryMu 
  defined below since previous it rendered HelioOrbElems to within 1% that were almost  
  exact to the observed values of Kepler-16. 
  */
  //HelioMu = BIGG * (body[0].dMass + body[iBody].dMass);
  //mTotal = body[0].dMass + body[1].dMass + ... + body[iTmpNumBodies - 1]
  //BaryMu = HelioMu * cube(1 - body[iBody].dMass / mTotal)
  dMu = elems.dMu;
  

  // Solving Kepler's Equation

  // Matrix transformation angles
  dL1 = dCosLongA * dCosArgP - dSinLongA * dSinArgP * dCosi;
  dM1 = dSinLongA * dCosArgP + dCosLongA * dSinArgP * dCosi;
  dN1 = dSinArgP * dSini;

  dL2 = -dCosLongA * dSinArgP - dSinLongA * dCosArgP * dCosi;
  dM2 = -dSinLongA * dSinArgP + dCosLongA * dCosArgP * dCosi;
  dN2 = dCosArgP * dSini;

  if (dEcc < 1) {
    dEccA = elems.dEccA;

    dCosEccA = cos(dEccA);
    dSinEccA = sin(dEccA);

    dXi = dSemi * (dCosEccA - dEcc);
    dEta = dSemi * pow(1. - dEcc * dEcc, 0.5) * dSinEccA;
  }
  if (dEcc > 1) {
    dHypA = elems.dHypA;

    dCoshHypA = cosh(dHypA);
    dSinhHypA = sinh(dHypA);

    dXi = dSemi * (dCoshHypA - dEcc);
    dEta = -dSemi * pow(dEcc * dEcc - 1., 0.5) * dSinhHypA;
  }

  //Defining Cartesian Coordinates
  dPos[0] = dL1 * dXi + dL2 * dEta;
  dPos[1] = dM1 * dXi + dM2 * dEta;
  dPos[2] = dN1 * dXi + dN2 * dEta;

  if (dEcc < 1) {
    dVelScl = pow(dMu * dSemi / dot(dPos, dPos), 0.5); // Time derivative of dEccA times semi-major axis
    dXi = -dVelScl * dSinEccA; // x-component of velocity
    dEta = dVelScl* pow(1. - dEcc * dEcc, 0.5) * dCosEccA; // y-component of velocity
  }
  if (dEcc > 1) {
    dVelScl = pow(-dMu * dSemi / dot(dPos, dPos), 0.5); // Time derivative of dHypA times semi-major axis
    dXi = -dVelScl * dSinhHypA; // x-component of velocity
    dEta = dVelScl * pow(dEcc * dEcc - 1.0, 0.5) * dCoshHypA; // y-component of velocity
  }
  dVel[0] = dL1 * dXi + dL2 * dEta;
  dVel[1] = dM1 * dXi + dM2 * dEta;
  dVel[2] = dN1 * dXi + dN2 * dEta;
  
}

double GetEccAnom(ELEMS elems) {
  double dMeanA, dEccA; 
  dMeanA = fmodPos(elems.dMeanA, 2. * PI);

  if (dMeanA == 0 || dMeanA == PI) {
    dEccA = 0; // Trivial solutions for the Eccentric Anomaly
  } else {
    double dEcc, dSinMeanA, dLow, dUp, dSinEccAe, dCosEccAe,
            f, fp, fpp, fppp, dx, dNext;
    dEcc = elems.dEcc;
    dSinMeanA = sin(dMeanA); 
    if (dSinMeanA > 0.0) {
      // 0.85 best value for numerical convergence according to Danby 1982 
      dEccA = dMeanA + 0.85 * dEcc; // A good guess for Newton-Rhapson method
      } else {
      dEccA = dMeanA - 0.85 * dEcc;
    }
    dLow = -2. * PI; 
    dUp = 2. * PI; // I do not understand these values yet...

    int i;
    for (i = 0; i < 32; i++) {
      dSinEccAe = sin(dEccA) * dEcc;
      dCosEccAe = cos(dEccA) * dEcc;
      f = dEccA - dSinEccAe - dMeanA; // function used for Newton–Raphson method
      fp = 1.0 - dCosEccAe; // p stands for prime. Derivative of f w.r.t dEccA
      fpp = dSinEccAe; // 2nd derivative
      fppp = dCosEccAe; // 3rd derivative

      if (f > 0.0) {
        dUp = dEccA;
      } else {
        dLow = dEccA;
      }

      dx = -f / fp; //First iteration of Newton-Rhapson 
      dx = -f / (fp + dx * fpp / 2.); //Second iteration of Newton-Rhapson 
      dx = -f / (fp + dx * fpp / 2. + dx * dx * fppp / 6.); //Third iteration of Newton-Rhapson 

      dNext = dEccA + dx;
      if (dEccA == dNext) {
        break;
      }
      if ((dNext > dLow) && (dNext < dUp)) {
        dEccA = dNext;
      } else {
        dEccA = (dLow + dUp) / 2.;
      }
      if ((dEccA == dLow) || (dEccA == dUp)) {
        break;
      }

      if (i > 31) {
        printf("Kepler soln failed\n");
        exit(1);
      } 
    }
  }
  return dEccA;
}

double GetHypAnom(ELEMS elems) {
  double dMeanA, dHypA;
  dMeanA = elems.dMeanA;
  if (dMeanA == 0.0) { // Trivial solution for the hyperbolic Hyperbolic Anomaly.
    dHypA = 0.0;
  } else {
    double dEcc, dSignMeanA, dLow, dUp, dSinhHypAe, dCoshHypAe,
            f, fp, fpp, fppp, dx, dNext;
    dEcc = elems.dEcc;
    // Found in Danby 1962 and other sources. They both claim that 1.8 is the best estimated guess
    // The Guess for dHypA is large but the constant accomodates for small values
    dSignMeanA = fiSign(dMeanA);
    if (dSignMeanA == 0) { // Can become 0 if fabs(dMeanA) < EPS defined in vplanet.h
      // David Graham dervied this expression for 0 < dHypA << 1
      // The expression below was never found anywhere. You can try to prove David wrong.
      // Or if he's not lazy, come up with an additional constant that improves this initial guess.
      dHypA = 3 * (dEcc - 1.0) / (2 * dMeanA);
    } else {
      dHypA = dSignMeanA * log(dSignMeanA * (2*dMeanA / dEcc) + 1.8);
    }

    int i;
    for (i = 0; i < 32; i++) {
      dSinhHypAe = sinh(dHypA) * dEcc;
      dCoshHypAe = cosh(dHypA) * dEcc;

      f = dSinhHypAe - dHypA - dMeanA; // function used for Newton–Raphson method
      fp = dCoshHypAe - 1.0; // p stands for prime. Derivative of f w.r.t dEccA
      fpp = dSinhHypAe; // 2nd derivative
      fppp = dCoshHypAe; // 3rd derivative


      dx = -f / fp; //First iteration of Newton-Rhapson 
      dx = -f / (fp + dx * fpp / 2.); //Second iteration of Newton-Rhapson 
      dx = -f / (fp + dx * fpp / 2. + dx * dx * fppp / 6.); //Third iteration of Newton-Rhapson 

      dNext = dHypA + dx;
      if (dHypA == dNext) { // If convergence, stop iterating
        break;
      } else {
        dHypA = dNext; // Goes to next iteration
      }
      
      if (i > 31) {
        printf("Kepler soln failed\n");
        exit(1);
      }
    }

  }
  return dHypA;
}

double GetMeanA(ELEMS elems) {
  double dMeanA, dEcc, dEccA, dHypA;
  dEcc = elems.dEcc;
  dEccA = elems.dEccA;
  dHypA = elems.dHypA;

  if (dEcc < 1.0) {
    dMeanA = dEccA - dEcc * sin(dEccA);
  }
  if (dEcc > 1.0) {
    dMeanA = dEcc * sinh(dHypA) - dHypA;
  }
  // Add options for dEcc == 1.0, question? I guess that's up for the next developer.
  return dMeanA;
}

void AssignBody2Elems(BODY *body, ELEMS elems, int iBody) {
  // use elems struct to generalize coordinates of different orbital elements
  elems.dSemi = body[iBody].dSemi;
  elems.dEcc = body[iBody].dEcc;
  elems.dInc = body[iBody].dInc;
  elems.dArgP = body[iBody].dArgP;
  elems.dLongP = body[iBody].dLongP;
  elems.dLongA = body[iBody].dLongA;
  elems.dMeanA = body[iBody].dMeanA;
  elems.dMeanL = body[iBody].dMeanL;
  elems.dEccA = GetEccAnom(elems); 
}

void fvBaryOrbElems2BaryCart(BODY *body, int iNumBodies, int iBody) {
  ELEMS elems;
  double *dPos, *dVel, mTotal, dBaryRelation, dHelioMu;
  dPos = malloc(3 * sizeof(double));
  dVel = malloc(3 * sizeof(double));
  // Switching and assigning elems struct
  // AssignBody2Elems(body, elems, iBody); // This function doesn't work. Help
  // use elems struct to generalize coordinates of different orbital elements
  elems.dSemi = body[iBody].dSemi;
  elems.dEcc = body[iBody].dEcc;
  elems.dInc = body[iBody].dInc;
  elems.dArgP = body[iBody].dArgP;
  elems.dLongP = body[iBody].dLongP;
  elems.dLongA = body[iBody].dLongA;
  elems.dMeanA = body[iBody].dMeanA;
  elems.dMeanL = body[iBody].dMeanL;
  if (elems.dEcc < 1) {
    elems.dEccA = GetEccAnom(elems);
  }
  if (elems.dEcc > 1) {
    elems.dHypA = GetHypAnom(elems);
  }   

  mTotal = TotalMass(body, iNumBodies);
  dBaryRelation = cube(1. - body[iBody].dMass / mTotal);
  dHelioMu = BIGG * mTotal; // (body[iBody].dMass + body[0].dMass) does not work here

  body[iBody].dBaryMu = dHelioMu * dBaryRelation;

  elems.dMu = body[iBody].dBaryMu;
  OrbElems2Cart(elems, dPos, dVel);
  for (int i = 0; i < 3; i++) {
    body[iBody].dBCartPos[i] = dPos[i];
    body[iBody].dBCartVel[i] = dVel[i];
  }

  free(dPos);
  free(dVel);  
}

void fvHelioOrbElems2HelioCart(BODY *body, int iNumBodies, int iBody) {
  ELEMS elems;
  double *dPos, *dVel, mTotal, dHelioMu;
  dPos = malloc(3 * sizeof(double));
  dVel = malloc(3 * sizeof(double));
  // Code below tries to replicate the above commented code
  // Note to self: Keep a similar format to this function but in vplanet units
  if (iBody == 0) {
    int i = 0;
    for (i = 0; i < 3; i++) {
    body[iBody].dHCartPos[i] = 0;
    body[iBody].dHCartVel[i] = 0;
    }
  } else { 
    // Switching and assigning elems struct
    // AssignBody2Elems(body, elems, iBody); // So far this function doesn't work. Help!
    // use elems struct to generalize coordinates of different orbital elements
    elems.dSemi = body[iBody].dSemi;
    elems.dEcc = body[iBody].dEcc;
    elems.dInc = body[iBody].dInc;
    elems.dArgP = body[iBody].dArgP;
    elems.dLongP = body[iBody].dLongP;
    elems.dLongA = body[iBody].dLongA;
    elems.dMeanA = body[iBody].dMeanA;
    elems.dMeanL = body[iBody].dMeanL;
    if (elems.dEcc < 1) {
      elems.dEccA = GetEccAnom(elems);
    }
    if (elems.dEcc > 1) {
      elems.dHypA = GetHypAnom(elems);
    }    

    // mTotal = TotalMass(body, iNumBodies);
    // dHelioMu = BIGG * mTotal;
    dHelioMu = BIGG * (body[0].dMass + body[iBody].dMass); // Trying this out again
    elems.dMu = dHelioMu;
    OrbElems2Cart(elems, dPos, dVel);
    for (int i = 0; i < 3; i++) {
      body[iBody].dHCartPos[i] = dPos[i];
      body[iBody].dHCartVel[i] = dVel[i];
    }
  }
  free(dPos);
  free(dVel);
}

void fvHelioCart2BaryCart(BODY *body, int iNumBodies, int iBody) {
  int i, iTmpBody;
  double *xcom, *vcom, mtotal;
  xcom = malloc(3 * sizeof(double));
  vcom = malloc(3 * sizeof(double));
  mtotal = TotalMass(body, iNumBodies);

  for (i = 0; i < 3; i++) {
    xcom[i] = 0;
    vcom[i] = 0;
    for (iTmpBody = 1; iTmpBody < iNumBodies; iTmpBody++) {
      xcom[i] += (body[iTmpBody].dMass * body[iTmpBody].dHCartPos[i] / mtotal);
      vcom[i] += (body[iTmpBody].dMass * body[iTmpBody].dHCartVel[i] / mtotal);
    }
  }
  for (i = 0; i < 3; i++) {
    body[iBody].dBCartPos[i] = body[iBody].dHCartPos[i] - xcom[i];
    body[iBody].dBCartVel[i] = body[iBody].dHCartVel[i] - vcom[i];
  }

  free(xcom);
  free(vcom);
}

void fvBaryCart2HelioCart(BODY *body, int iBody) {
  int i = 0;
  for (i = 0; i < 3; i++) {
    body[iBody].dHCartPos[i] = body[iBody].dBCartPos[i] - body[0].dBCartPos[i];
    body[iBody].dHCartVel[i] = body[iBody].dBCartVel[i] - body[0].dBCartVel[i];
  }
}



void Cart2OrbElems(ELEMS elems, double *dPos, double *dVel) {

}


void fvBaryCart2HelioOrbElems(BODY *body, int iNumBodies, int iBody) {
  double rsq, normr, vsq, mTotal, mu, *h, hsq, normh, sinwf, coswf, sinfAngle,
        cosfAngle, rdot, sinw, cosw, f, cosE, coshH, sinhH;

  h = malloc(3 * sizeof(double));
  // First convert from Barycentric to heliocentric
  // Helio values are stored in body[iBody].daCartPos and body[iBody].daCartVel

  fvBaryCart2HelioCart(body, iBody);

  if (iBody == 0) {
    body[iBody].dSemi  = 0;
    body[iBody].dEcc   = 0;
    body[iBody].dInc   = 0;
    body[iBody].dLongA = 0;
    body[iBody].dArgP  = 0;
    body[iBody].dLongP = 0;
    body[iBody].dMeanA = 0;
    body[iBody].dMeanL = 0;
  } else {

    // Solve for various values that are used repeatedly
    // Solve for h = r X v
    cross(body[iBody].dHCartPos, body[iBody].dHCartVel, h);
    hsq   = h[0] * h[0] + h[1] * h[1] + h[2] * h[2];            // ||h||^2
    normh = sqrt(hsq);                                          // ||h||
    vsq   = body[iBody].dHCartVel[0] * body[iBody].dHCartVel[0] // ||v||^2
          + body[iBody].dHCartVel[1] * body[iBody].dHCartVel[1] +
          body[iBody].dHCartVel[2] * body[iBody].dHCartVel[2];
    rsq = body[iBody].dHCartPos[0] * body[iBody].dHCartPos[0] // ||r||^2
          + body[iBody].dHCartPos[1] * body[iBody].dHCartPos[1] +
          body[iBody].dHCartPos[2] * body[iBody].dHCartPos[2];
    normr = sqrt(rsq); // ||r||
    rdot  = (body[iBody].dHCartPos[0] * body[iBody].dHCartVel[0] +
            body[iBody].dHCartPos[1] * body[iBody].dHCartVel[1] +
            body[iBody].dHCartPos[2] * body[iBody].dHCartVel[2]) /
           normr;
    //mu              = BIGG * (body[iBody].dMass + body[0].dMass); // G(M+m)
    // mTotal = TotalMass(body, iNumBodies);
    // mu = BIGG * mTotal;
    mu = BIGG * (body[iBody].dMass + body[0].dMass); // trying this out
    // body[iBody].dMu = mu;

    // Solve for semi-major axis
    body[iBody].dSemi = 1 / (2 / normr - vsq / mu);

    // Solve for eccentricity
    body[iBody].dEccSq = 1.0 - hsq / (mu * body[iBody].dSemi);
    if (body[iBody].dEccSq < 1.0e-15) {
      body[iBody].dEccSq = 0.0; // Unfortunately machine precision limits the accuracy of dEccSq
    }
    body[iBody].dEcc = sqrt(body[iBody].dEccSq);

    // Solve for inclination
    body[iBody].dInc  = acos(h[2] / normh);
    body[iBody].dSinc = 0.5 * sin(body[iBody].dInc); // For DistOrb usage

    // Solve for w and f
    if (body[iBody].dInc == 0.0) {
      body[iBody].dLongA = 0; // LongA is actually undefined. Should I leave it as 0, question?
      // Leave it as zero. Maybe we can still use it when defining dLongP = dLongA + dArgP 
      sinwf = body[iBody].dHCartPos[1] / normr; // Different definition when dInc = 0
      coswf = body[iBody].dHCartPos[0] / normr;           
    } else {
      body[iBody].dLongA = fmodPos(atan2(h[0], -h[1]), 2. * PI);
      sinwf = body[iBody].dHCartPos[2] /
              (normr * sin(body[iBody].dInc));
      coswf = (body[iBody].dHCartPos[0] / normr +
              sin(body[iBody].dLongA) * sinwf * cos(body[iBody].dInc)) /
              cos(body[iBody].dLongA);
    }

    if (body[iBody].dEcc == 0.0) {
      body[iBody].dArgP  = 0;
      body[iBody].dLongP = 0;
      body[iBody].dMeanA = 0;
      body[iBody].dMeanL = 0; 
      if (body[iBody].dInc == 0.0) { // dEcc = dInc = 0
        // The values below don't exist
        body[iBody].dLongA = 0;
        // Only the true longitude exists. Make a variable for this?
      } else { // dEcc = 0, dInc != 0
        double *dLineOfNodes, dNormLineNodes, dArgLatitude;
        dLineOfNodes = malloc(3 * sizeof(double));
        dLineOfNodes[0] = -h[1]; // z x h, z is the unit vector in the z direction
        dLineOfNodes[1] = +h[0];
        dNormLineNodes = sqrt(dot(dLineOfNodes, dLineOfNodes));
        dArgLatitude = acos(dot(dLineOfNodes, body[iBody].dHCartPos) / (dNormLineNodes * normr));
        free(dLineOfNodes);
      }
    } else if (body[iBody].dEcc > 0) { // dEcc > 0, dInc can be any real value within its domain.
      sinfAngle = body[iBody].dSemi * (1 - body[iBody].dEccSq) * rdot /
                  (normh * body[iBody].dEcc);
      cosfAngle = (body[iBody].dSemi * (1 - body[iBody].dEccSq) / normr - 1) /
                  body[iBody].dEcc;

      if (fabs(cosfAngle - 1.0) < 1e-14) { // There are rounding errors at such precise values. We try to avoid cosfAngle > 1
        cosfAngle = 1.0;
        sinfAngle = 0.0;
      }
      sinw = sinwf * cosfAngle - coswf * sinfAngle;
      cosw = sinwf * sinfAngle + coswf * cosfAngle;

      body[iBody].dArgP  = fmodPos(atan2(sinw, cosw), 2 * PI);
      body[iBody].dLongP = fmodPos(body[iBody].dArgP + body[iBody].dLongA, 2 * PI);

      f = fmodPos(atan2(sinfAngle, cosfAngle), 2 * PI);

      if (fabs(cosfAngle - 1) > 0) {
        cosfAngle = cos(f);
        sinfAngle = sin(f);
      }      

      // Calculate Mean anomaly
      // Defitions change since elliptical and hyperbolic orbits have different Mean Anomalies
      if (body[iBody].dEcc < 1.0) { // We use the Eccentric Anomaly, E
        cosE = (cosfAngle + body[iBody].dEcc) /
              (1.0 + body[iBody].dEcc * cosfAngle);
        if (fabs(fabs(cosE) - 1) < 1e-11) { // Error gets larger for longer simulations with smaller timesteps
          /* If there is numerical error such that abs(cosE)>1, then use the small
            angle approximation to find E */
          body[iBody].dEccA =
                (1 + (body[iBody].dEccSq - 1) * (cosfAngle * cosfAngle) -
                body[iBody].dEccSq) /
                (1 + body[iBody].dEcc * cosfAngle);
        } else {
          if (fabs(cosE) > 1) {
            // Need io here to check verbosity XXX
            fprintf(stderr, "ERROR: cosine of the Eccentric Anomaly is greater than 1. Please rerun with a smaller timestep.");
            exit(EXIT_EXE);
          }
          body[iBody].dEccA = acos(cosE);

          // If the planet is in the second half of the orbit, we need -acos(cosE)
          // + 2PI This keeps Mean A in [0, 2PI]
          if (f > PI) {
            body[iBody].dEccA = -body[iBody].dEccA + 2 * PI;
          }
        }
        body[iBody].dHypA = 0.0; // The value is actually undefined but it is left as zero as a band-aid solution
        body[iBody].dMeanA =
              fmodPos(body[iBody].dEccA - body[iBody].dEcc * sin(body[iBody].dEccA), 2 * PI);
        body[iBody].dMeanL = fmodPos(body[iBody].dMeanA + body[iBody].dLongP, 2 * PI);

        body[iBody].dMeanMotion = sqrt(mu / (body[iBody].dSemi * body[iBody].dSemi * body[iBody].dSemi));
        body[iBody].dOrbPeriod  = 2.0 * PI / body[iBody].dMeanMotion;
        body[iBody].dPinc       = body[iBody].dSinc * sin(body[iBody].dLongA);
        body[iBody].dQinc       = body[iBody].dSinc * cos(body[iBody].dLongA);
        body[iBody].dHecc       = body[iBody].dEcc * sin(body[iBody].dLongP);
        body[iBody].dKecc       = body[iBody].dEcc * cos(body[iBody].dLongP);
      }
      if (body[iBody].dEcc > 1.0) { // We use the Hyperbolic Anomaly, H
        // Calculate Mean Anomaly
        //coshH = (cosfAngle + body[iBody].dBaryEcc) /
        //        (1.0 + body[iBody].dBaryEcc * cosfAngle);
        /*
        For hyperbolic orbits f lies only in Quadrants I and IV while acos() lies in 
        Quadrants I and II. If in Quadrant II, must switch to Quadrant IV.
        */
        if (cosfAngle < 0) {
          sinfAngle = -sinfAngle;
          // Be Careful. If ever using acos(cosfAngle), it would produce the incorrect angle
        }          
        // One loses the sign of dHypA when using coshH. sinhH keeps the sign. 
        sinhH = sqrt(body[iBody].dEcc * body[iBody].dEcc - 1) * sinfAngle / 
                (1.0 + body[iBody].dEcc * cosfAngle);

        body[iBody].dHypA = asinh(sinhH);
        body[iBody].dEccA = 0.0; // This is actually undefined. Should we make this nan, question?

        body[iBody].dMeanA = body[iBody].dEcc * sinh(body[iBody].dHypA) - body[iBody].dHypA;
        body[iBody].dMeanL = body[iBody].dMeanA + body[iBody].dLongP;

        body[iBody].dMeanMotion = sqrt(-mu / (body[iBody].dSemi * body[iBody].dSemi * body[iBody].dSemi));
        body[iBody].dOrbPeriod = 0.0; // This value should actually be nan or infinity. How do I define this, question?        
      }
      
    }
  }
  free(h);
}

void fvBaryCart2BaryOrbElems(BODY *body, int iNumBodies, int iBody) {

  double rsq, normr, vsq, dHelioMu, mu, mTotal, dBaryRelation, *h, hsq, normh, sinwf, coswf, sinfAngle,
      cosfAngle, rdot, sinw, cosw, f, cosE, coshH, sinhH;
  // Solve for various values that are used repeatedly
  // Solve for specific angular momentum h = r X v
  h = malloc(3 * sizeof(double));
  cross(body[iBody].dBCartPos, body[iBody].dBCartVel, h);
  hsq   = h[0] * h[0] + h[1] * h[1] + h[2] * h[2];            // ||h||^2
  normh = sqrt(hsq);                                          // ||h||
  vsq   = body[iBody].dBCartVel[0] * body[iBody].dBCartVel[0] // ||v||^2
        + body[iBody].dBCartVel[1] * body[iBody].dBCartVel[1] +
        body[iBody].dBCartVel[2] * body[iBody].dBCartVel[2];
  rsq = body[iBody].dBCartPos[0] * body[iBody].dBCartPos[0] // ||r||^2
        + body[iBody].dBCartPos[1] * body[iBody].dBCartPos[1] +
        body[iBody].dBCartPos[2] * body[iBody].dBCartPos[2];
  normr = sqrt(rsq); // ||r||
  rdot  = (body[iBody].dBCartPos[0] * body[iBody].dBCartVel[0] +
          body[iBody].dBCartPos[1] * body[iBody].dBCartVel[1] +
          body[iBody].dBCartPos[2] * body[iBody].dBCartVel[2]) /
          normr;
  //HelioMu = BIGG * (body[0].dMass + body[iBody].dMass);
  //mTotal = body[0].dMass + body[1].dMass + ... + body[i == iBody].dMass + ... + body[iTmpNumBodies - 1]
  //BaryMu = HelioMu * (dMassNo_iBody / mTotal)^3
  mTotal = TotalMass(body, iNumBodies);
  dBaryRelation = cube(1. - body[iBody].dMass / mTotal);
  dHelioMu = BIGG * mTotal; // (body[iBody].dMass + body[0].dMass);
  mu = dHelioMu * dBaryRelation;
  body[iBody].dBaryMu = mu;
  // Solve for semi-major axis
  body[iBody].dBarySemi = 1 / (2 / normr - vsq / mu);

  // Solve for eccentricity
  body[iBody].dBaryEccSq = 1.0 - hsq / (mu * body[iBody].dBarySemi);
  if (body[iBody].dEccSq < 1.0e-15) {
    body[iBody].dEccSq = 0.0; // Unfortunately machine precision limits the accuracy of dEccSq
  }  
  body[iBody].dBaryEcc = sqrt(body[iBody].dBaryEccSq);

  // Solve for inclination
  body[iBody].dBaryInc  = acos(h[2] / normh);

  // dSinc might not need to be used for BaryOrbElems
  // body[iBody].dBarySinc = 0.5 * sin(body[iBody].dBaryInc); // For DistOrb usage


  // Solve for longitude of ascending node, w, and f
  if (body[iBody].dBaryInc != 0.0) {
    body[iBody].dBaryLongA = fmodPos(atan2(h[0], -h[1]), 2. * PI);
    sinwf = body[iBody].dBCartPos[2] /
            (normr * sin(body[iBody].dBaryInc));
    coswf = (body[iBody].dBCartPos[0] / normr +
            sin(body[iBody].dBaryLongA) * sinwf * cos(body[iBody].dBaryInc)) /
            cos(body[iBody].dBaryLongA);
  } else { // Different definition when dBaryInc = 0
    body[iBody].dBaryLongA = 0.0; //It's actually undefined but this will do for now...
    sinwf = body[iBody].dBCartPos[1] / normr;
    coswf = body[iBody].dBCartPos[0] / normr;
  }
  if (body[iBody].dBaryEcc != 0.0) { // No true anomaly for circular orbits
    sinfAngle = body[iBody].dBarySemi * (1. - body[iBody].dBaryEccSq) * rdot /
                (normh * body[iBody].dBaryEcc);
    cosfAngle = (body[iBody].dBarySemi * (1. - body[iBody].dBaryEccSq) / normr - 1) /
                body[iBody].dBaryEcc;
    if (fabs(cosfAngle - 1.0) < 1e-14) { // There are rounding errors at such precise values. We try to avoid cosfAngle > 1
      cosfAngle = 1.0;
      sinfAngle = 0.0;
    }
    sinw = sinwf * cosfAngle - coswf * sinfAngle;
    cosw = sinwf * sinfAngle + coswf * cosfAngle;

    body[iBody].dBaryArgP  = fmodPos(atan2(sinw, cosw), 2. * PI);
    body[iBody].dBaryLongP = fmodPos(body[iBody].dBaryArgP + body[iBody].dBaryLongA, 2. * PI);
    f = fmodPos(atan2(sinfAngle, cosfAngle), 2. * PI);

    if (fabs(cosfAngle - 1) > 0) {
      cosfAngle = cos(f);
      sinfAngle = sin(f);
    }

    
    if (body[iBody].dBaryEcc < 1.0) { //Using EccA to calculate other orbital elements
      // Calculate Mean anomaly
      cosE = (cosfAngle + body[iBody].dBaryEcc) /
              (1.0 + body[iBody].dBaryEcc * cosfAngle);
      if (fabs(fabs(cosE) - 1) < 1e-11) { // Error gets larger for longer simulations with smaller timesteps
        /* If there is numerical error such that abs(cosE)>1, then use the small
            angle approximation to find E */
        body[iBody].dBaryEccA =
              (1 + (body[iBody].dBaryEccSq - 1) * (cosfAngle * cosfAngle) -
                body[iBody].dBaryEccSq) /
              (1 + body[iBody].dBaryEcc * cosfAngle);
      } else {
        body[iBody].dBaryEccA = acos(cosE);

        // If the planet is in the second half of the orbit, we need -acos(cosE)
        // + 2PI This keeps Mean A in [0, 2PI]
        if (f > PI) {
          body[iBody].dBaryEccA = -body[iBody].dBaryEccA + 2 * PI;
        }
      }

      body[iBody].dBaryMeanA =
            fmodPos(body[iBody].dBaryEccA - body[iBody].dBaryEcc * sin(body[iBody].dBaryEccA), 2 * PI);
      // Calculating Mean Longitude
      body[iBody].dBaryMeanL =  fmodPos(body[iBody].dBaryMeanA + body[iBody].dBaryLongP, 2 * PI);            

      // Calculating Mean Motion
      body[iBody].dBaryMeanMotion = 
              sqrt(mu / (body[iBody].dBarySemi * body[iBody].dBarySemi * body[iBody].dBarySemi));
      // Calculating Orbital Period
      body[iBody].dBaryOrbPeriod = 2.0 * PI / body[iBody].dBaryMeanMotion;
    }
    if (body[iBody].dBaryEcc > 1.0) { // Using HypA to calculate other orbital elements.
      // Calculate Mean Anomaly
      //coshH = (cosfAngle + body[iBody].dBaryEcc) /
      //        (1.0 + body[iBody].dBaryEcc * cosfAngle);
      /*
      For hyperbolic orbits f lies only in Quadrants I and IV while acos() lies in 
      Quadrants I and II. If in Quadrant II, must switch to Quadrant IV.
      */
      if (cosfAngle < 0) {
        sinfAngle = -sinfAngle; 
        // Be Careful. If ever using acos(cosfAngle), it would produce the incorrect angle
      }
      // You loses the sign of dHypA when using acosh(coshH). asinh(sinhH) keeps the sign. 
      sinhH = sqrt(body[iBody].dBaryEcc * body[iBody].dBaryEcc - 1) * sinfAngle / 
              (1.0 + body[iBody].dBaryEcc * cosfAngle);

      body[iBody].dBaryHypA = asinh(sinhH);

      body[iBody].dBaryEccA = 0.0; // This is actually undefined. Should we make this nan, question?

      body[iBody].dBaryMeanA = body[iBody].dBaryEcc * sinh(body[iBody].dBaryHypA) - body[iBody].dBaryHypA;
      // Calculating Mean Longitude
      body[iBody].dBaryMeanL =  body[iBody].dBaryMeanA + body[iBody].dBaryLongP;
      // Calculating Mean Motion
      body[iBody].dBaryMeanMotion = 
              sqrt(-mu / (body[iBody].dBarySemi * body[iBody].dBarySemi * body[iBody].dBarySemi));
      // Calculate Orbital Period
      body[iBody].dBaryOrbPeriod = 0.0; // The orbital period actually doesn't exist. Need to change?      
    }
  }
  free(h);
}


// Functions below are EXACTLY the same as in distorb.c, but needed in SpiNBody
// Should be relocated to system.c?

//
// void kepler_eqn(BODY *body, int iBody) { //Same as in distorb.c
//   double di1, di2, di3, fi, fi1, fi2, fi3;
//   if (body[iBody].dMeanA == 0) {
//     body[iBody].dEccA = 0;
//   } else {
//     body[iBody].dEccA = body[iBody].dMeanA +
//     signf(sin(body[iBody].dMeanA))*0.85*body[iBody].dEcc; di3 = 1.0;
//
//     while (di3 > 1e-15) {
//       fi = body[iBody].dEccA - body[iBody].dEcc*sin(body[iBody].dEccA) -
//       body[iBody].dMeanA; fi1 = 1.0 -
//       body[iBody].dEcc*cos(body[iBody].dEccA); fi2 =
//       body[iBody].dEcc*sin(body[iBody].dEccA); fi3 =
//       body[iBody].dEcc*cos(body[iBody].dEccA); di1 = -fi/fi1; di2 =
//       -fi/(fi1+0.5*di1*fi2); di3 =
//       -fi/(fi1+0.5*di2*fi2+1./6.*pow(di2,2)*fi3); body[iBody].dEccA += di3;
//     }
//   }
// }
//
// double signf(double value) { //Same as in distorb.c
//   if (value > 0) return 1.;
//   if (value < 0) return -1.;
//   return 0;
// }
//
// double xinit(BODY *body, int iBody) {
//   return body[iBody].dSemi/AUM * (cos(body[iBody].dEccA) - body[iBody].dEcc);
// }
//
// double yinit(BODY *body, int iBody) {
//   return body[iBody].dSemi/AUM * sqrt(1.0-pow(body[iBody].dEcc,2)) *
//   sin(body[iBody].dEccA);
// }
//
// double vxi(BODY *body, int iBody) {
//   double x, y, mu, n;
//   x = xinit(body, iBody);
//   y = yinit(body, iBody);
//   mu = pow(KGAUSS,2)*(body[0].dMass+body[iBody].dMass)/MSUN;
//   n = sqrt(mu/pow(body[iBody].dSemi/AUM,3));
//   return
//   -pow(body[iBody].dSemi/AUM,2)*n*sin(body[iBody].dEccA)/sqrt(pow(x,2)+pow(y,2));
// }
//
// double vyi(BODY *body, int iBody) {
//   double x, y, mu, n, v;
//   x = xinit(body, iBody);
//   y = yinit(body, iBody);
//   mu = pow(KGAUSS,2)*(body[0].dMass+body[iBody].dMass)/MSUN;
//   n = sqrt(mu/pow(body[iBody].dSemi/AUM,3));
//   v =
//   pow(body[iBody].dSemi/AUM,2)*n*sqrt((1.0-pow(body[iBody].dEcc,2))/(pow(x,2)+pow(y,2)))*cos(body[iBody].dEccA);
//   return v;
// }
//
// double xangle1(BODY *body, int iBody) {
//   return cos(body[iBody].dLongA)*cos(body[iBody].dLongP-body[iBody].dLongA) -
//   sin(body[iBody].dLongA)*sin(body[iBody].dLongP-body[iBody].dLongA)*(1.0-2.*pow(body[iBody].dSinc,2));
// }
//
// double xangle2(BODY *body, int iBody) {
//   return -cos(body[iBody].dLongA)*sin(body[iBody].dLongP-body[iBody].dLongA)
//   -
//   sin(body[iBody].dLongA)*cos(body[iBody].dLongP-body[iBody].dLongA)*(1.0-2.*pow(body[iBody].dSinc,2));
// }
//
// double yangle1(BODY *body, int iBody) {
//   return sin(body[iBody].dLongA)*cos(body[iBody].dLongP-body[iBody].dLongA) +
//   cos(body[iBody].dLongA)*sin(body[iBody].dLongP-body[iBody].dLongA)*(1.0-2.*pow(body[iBody].dSinc,2));
// }
//
// double yangle2(BODY *body, int iBody) {
//   return -sin(body[iBody].dLongA)*sin(body[iBody].dLongP-body[iBody].dLongA)
//   +
//   cos(body[iBody].dLongA)*cos(body[iBody].dLongP-body[iBody].dLongA)*(1.0-2.*pow(body[iBody].dSinc,2));
// }
//
// double zangle1(BODY *body, int iBody) {
//   return
//   sin(body[iBody].dLongP-body[iBody].dLongA)*(2.*body[iBody].dSinc*sqrt(1.0-pow(body[iBody].dSinc,2)));
// }
//
// double zangle2(BODY *body, int iBody) {
//   return
//   cos(body[iBody].dLongP-body[iBody].dLongA)*(2.*body[iBody].dSinc*sqrt(1.0-pow(body[iBody].dSinc,2)));
// }

//========================== End Coordinate Changes ============================

void CountHaltsSpiNBody(HALT *halt, int *iHalt) {
  // What halts do we want? Collision?
}

void VerifyHaltSpiNBody(BODY *body, CONTROL *control, OPTIONS *options,
                        int iBody, int *iHalt) {
}

//============================ Writing Functions ===============================

//HelioCart writeout

void WriteHelioPosX(BODY *body, CONTROL *control, OUTPUT *output,
                    SYSTEM *system, UNITS *units, UPDATE *update, int iBody,
                    double *dTmp, char cUnit[]) {
  //*dTmp = body[iBody].dHelioPosX;
  *dTmp = body[iBody].dHCartPos[0];
  strcpy(cUnit, "");
}

void WriteHelioPosY(BODY *body, CONTROL *control, OUTPUT *output,
                    SYSTEM *system, UNITS *units, UPDATE *update, int iBody,
                    double *dTmp, char cUnit[]) {
  //*dTmp = body[iBody].dHelioPosY;
  *dTmp = body[iBody].dHCartPos[1];
  strcpy(cUnit, "");
}

void WriteHelioPosZ(BODY *body, CONTROL *control, OUTPUT *output,
                    SYSTEM *system, UNITS *units, UPDATE *update, int iBody,
                    double *dTmp, char cUnit[]) {
  //*dTmp = body[iBody].dHelioPosZ;
  *dTmp = body[iBody].dHCartPos[2];
  strcpy(cUnit, "");
}

void WriteHelioVelX(BODY *body, CONTROL *control, OUTPUT *output, SYSTEM *system,
               UNITS *units, UPDATE *update, int iBody, double *dTmp,
               char cUnit[]) {
  //*dTmp = body[iBody].dHelioVelX;
  *dTmp = body[iBody].dHCartVel[0];
  strcpy(cUnit, "");
}

void WriteHelioVelY(BODY *body, CONTROL *control, OUTPUT *output, SYSTEM *system,
               UNITS *units, UPDATE *update, int iBody, double *dTmp,
               char cUnit[]) {
  //*dTmp = body[iBody].dHelioVelY;
  *dTmp = body[iBody].dHCartVel[1];
  strcpy(cUnit, "");
}

void WriteHelioVelZ(BODY *body, CONTROL *control, OUTPUT *output, SYSTEM *system,
               UNITS *units, UPDATE *update, int iBody, double *dTmp,
               char cUnit[]) {
  //*dTmp = body[iBody].dHelioVelZ;
  *dTmp = body[iBody].dHCartVel[2];
  strcpy(cUnit, "");
}

//BaryCart writeout

void WriteBaryPosX(BODY *body, CONTROL *control, OUTPUT *output,
                    SYSTEM *system, UNITS *units, UPDATE *update, int iBody,
                    double *dTmp, char cUnit[]) {
  //*dTmp = body[iBody].dPositionX;
  *dTmp = body[iBody].dBCartPos[0];
  strcpy(cUnit, "");
}

void WriteBaryPosY(BODY *body, CONTROL *control, OUTPUT *output,
                    SYSTEM *system, UNITS *units, UPDATE *update, int iBody,
                    double *dTmp, char cUnit[]) {
  //*dTmp = body[iBody].dPositionY;
  *dTmp = body[iBody].dBCartPos[1];
  strcpy(cUnit, "");
}

void WriteBaryPosZ(BODY *body, CONTROL *control, OUTPUT *output,
                    SYSTEM *system, UNITS *units, UPDATE *update, int iBody,
                    double *dTmp, char cUnit[]) {
  //*dTmp = body[iBody].dPositionZ;
  *dTmp = body[iBody].dBCartPos[2];
  strcpy(cUnit, "");
}

void WriteBaryVelX(BODY *body, CONTROL *control, OUTPUT *output, SYSTEM *system,
               UNITS *units, UPDATE *update, int iBody, double *dTmp,
               char cUnit[]) {
  //*dTmp = body[iBody].dVelX;
  *dTmp = body[iBody].dBCartVel[0];
  strcpy(cUnit, "");
}

void WriteBaryVelY(BODY *body, CONTROL *control, OUTPUT *output, SYSTEM *system,
               UNITS *units, UPDATE *update, int iBody, double *dTmp,
               char cUnit[]) {
  //*dTmp = body[iBody].dVelY;
  *dTmp = body[iBody].dBCartVel[1];
  strcpy(cUnit, "");
}

void WriteBaryVelZ(BODY *body, CONTROL *control, OUTPUT *output, SYSTEM *system,
               UNITS *units, UPDATE *update, int iBody, double *dTmp,
               char cUnit[]) {
  //*dTmp = body[iBody].dVelZ;
  *dTmp = body[iBody].dBCartVel[2];
  strcpy(cUnit, "");
}


//HelioOrbElems Writeout


void WriteHelioSemi(BODY *body, CONTROL *control, OUTPUT *output,
                              SYSTEM *system, UNITS *units, UPDATE *update,
                              int iBody, double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dHelioSemi;

  if (output->bDoNeg[iBody]) {
    *dTmp *= output->dNeg;
       strcpy(cUnit, output->cNeg);
  } else {
    *dTmp /= fdUnitsLength(units->iLength);
    fsUnitsLength(units->iLength, cUnit);
  }
}

void WriteHelioEcc(BODY *body, CONTROL *control, OUTPUT *output,
                            SYSTEM *system, UNITS *units, UPDATE *update,
                            int iBody, double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dHelioEcc;
}

void WriteHelioInc(BODY *body, CONTROL *control, OUTPUT *output,
                            SYSTEM *system, UNITS *units, UPDATE *update,
                            int iBody, double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dHelioInc;

  if (output->bDoNeg[iBody]) {
    *dTmp *= output->dNeg;
    strcpy(cUnit, output->cNeg);
  } else {
    *dTmp /= fdUnitsAngle(units->iAngle);
    fsUnitsAngle(units->iAngle, cUnit);
  }
}

void WriteHelioLongA(BODY *body, CONTROL *control, OUTPUT *output,
                      SYSTEM *system, UNITS *units, UPDATE *update, int iBody,
                      double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dHelioLongA;

  if (output->bDoNeg[iBody]) {
    *dTmp *= output->dNeg;
    strcpy(cUnit, output->cNeg);
  } else {
    *dTmp /= fdUnitsAngle(units->iAngle);
    fsUnitsAngle(units->iAngle, cUnit);
  }
}

void WriteHelioArgP(BODY *body, CONTROL *control, OUTPUT *output,
                    SYSTEM *system, UNITS *units, UPDATE *update, int iBody,
                    double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dHelioArgP;

  if (output->bDoNeg[iBody]) {
    *dTmp *= output->dNeg;
    strcpy(cUnit, output->cNeg);
  } else {
    *dTmp /= fdUnitsAngle(units->iAngle);
    fsUnitsAngle(units->iAngle, cUnit);
  }
}

void WriteHelioLongP(BODY *body, CONTROL *control, OUTPUT *output,
                      SYSTEM *system, UNITS *units, UPDATE *update, int iBody,
                      double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dHelioLongP;

  if (output->bDoNeg[iBody]) {
    *dTmp *= output->dNeg;
    strcpy(cUnit, output->cNeg);
  } else {
    *dTmp /= fdUnitsAngle(units->iAngle);
    fsUnitsAngle(units->iAngle, cUnit);
  }
}

void WriteHelioMeanA(BODY *body, CONTROL *control, OUTPUT *output,
                      SYSTEM *system, UNITS *units, UPDATE *update, int iBody,
                      double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dHelioMeanA;
  // MeanA only represented in degrees in a bound orbit
  if (body[iBody].dEcc < 1) {
    if (output->bDoNeg[iBody]) {
      *dTmp *= output->dNeg;
      strcpy(cUnit, output->cNeg);
    } else {
      *dTmp /= fdUnitsAngle(units->iAngle);
      fsUnitsAngle(units->iAngle, cUnit);
    }
  } // In a hyperbolic orbit MeanL is represented as an area in radians
}

void WriteHelioMeanL(BODY *body, CONTROL *control, OUTPUT *output,
                    SYSTEM *system, UNITS *units, UPDATE *update, int iBody,
                    double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dHelioMeanL;
  // MeanL only represented in degrees in a bound orbit
  if (body[iBody].dEcc < 1) {
    if (output->bDoNeg[iBody]) {
      *dTmp *= output->dNeg;
      strcpy(cUnit, output->cNeg);
    } else {
      *dTmp /= fdUnitsAngle(units->iAngle);
      fsUnitsAngle(units->iAngle, cUnit);
    }
  } // In a hyperbolic orbit MeanL is represented as an area in radians
}

void WriteHelioEccA(BODY *body, CONTROL *control, OUTPUT *output,
                    SYSTEM *system, UNITS *units, UPDATE *update, int iBody,
                    double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dHelioEccA;

  if (output->bDoNeg[iBody]) {
    *dTmp *= output->dNeg;
    strcpy(cUnit, output->cNeg);
  } else {
    *dTmp /= fdUnitsAngle(units->iAngle);
    fsUnitsAngle(units->iAngle, cUnit);
  }
}

void WriteHelioHypA(BODY *body, CONTROL *control, OUTPUT *output,
                    SYSTEM *system, UNITS *units, UPDATE *update, int iBody,
                    double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dHelioHypA;
  // Do not convert to degrees
  // Hyperbolic Anomaly is a ratio of areas represented only in radians
}


//BaryOrbElems Writeout


void WriteBarySemi(BODY *body, CONTROL *control, OUTPUT *output,
                            SYSTEM *system, UNITS *units, UPDATE *update,
                            int iBody, double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dBarySemi;

  if (output->bDoNeg[iBody]) {
    *dTmp *= output->dNeg;
       strcpy(cUnit, output->cNeg);
  } else {
    *dTmp /= fdUnitsLength(units->iLength);
    fsUnitsLength(units->iLength, cUnit);
  }
}

void WriteBaryEcc(BODY *body, CONTROL *control, OUTPUT *output,
                            SYSTEM *system, UNITS *units, UPDATE *update,
                            int iBody, double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dBaryEcc;
}

void WriteBaryInc(BODY *body, CONTROL *control, OUTPUT *output,
                            SYSTEM *system, UNITS *units, UPDATE *update,
                            int iBody, double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dBaryInc;
  if (output->bDoNeg[iBody]) {
    *dTmp *= output->dNeg;
    strcpy(cUnit, output->cNeg);
  } else {
    *dTmp /= fdUnitsAngle(units->iAngle);
    fsUnitsAngle(units->iAngle, cUnit);
  }
}

void WriteBaryLongA(BODY *body, CONTROL *control, OUTPUT *output,
                    SYSTEM *system, UNITS *units, UPDATE *update, int iBody,
                    double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dBaryLongA;

  if (output->bDoNeg[iBody]) {
    *dTmp *= output->dNeg;
    strcpy(cUnit, output->cNeg);
  } else {
    *dTmp /= fdUnitsAngle(units->iAngle);
    fsUnitsAngle(units->iAngle, cUnit);
  }
}

void WriteBaryArgP(BODY *body, CONTROL *control, OUTPUT *output,
                    SYSTEM *system, UNITS *units, UPDATE *update, int iBody,
                    double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dBaryArgP;

  if (output->bDoNeg[iBody]) {
    *dTmp *= output->dNeg;
    strcpy(cUnit, output->cNeg);
  } else {
    *dTmp /= fdUnitsAngle(units->iAngle);
    fsUnitsAngle(units->iAngle, cUnit);
  }
}

void WriteBaryLongP(BODY *body, CONTROL *control, OUTPUT *output,
                    SYSTEM *system, UNITS *units, UPDATE *update, int iBody,
                    double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dBaryLongP;

  if (output->bDoNeg[iBody]) {
    *dTmp *= output->dNeg;
    strcpy(cUnit, output->cNeg);
  } else {
    *dTmp /= fdUnitsAngle(units->iAngle);
    fsUnitsAngle(units->iAngle, cUnit);
  }
}

void WriteBaryMeanA(BODY *body, CONTROL *control, OUTPUT *output,
                    SYSTEM *system, UNITS *units, UPDATE *update, int iBody,
                    double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dBaryMeanA;
  // MeanA only represented in degrees in a bound orbit
  if (body[iBody].dBaryEcc < 1) {
    if (output->bDoNeg[iBody]) {
      *dTmp *= output->dNeg;
      strcpy(cUnit, output->cNeg);
    } else {
      *dTmp /= fdUnitsAngle(units->iAngle);
      fsUnitsAngle(units->iAngle, cUnit);
    }
  } // In a hyperbolic orbit MeanA is represented as an area in radians
}

void WriteBaryMeanL(BODY *body, CONTROL *control, OUTPUT *output,
                    SYSTEM *system, UNITS *units, UPDATE *update, int iBody,
                    double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dBaryMeanL;
  // MeanL only represented in degrees in a bound orbit
  if (body[iBody].dBaryEcc < 1) {
    if (output->bDoNeg[iBody]) {
      *dTmp *= output->dNeg;
      strcpy(cUnit, output->cNeg);
    } else {
      *dTmp /= fdUnitsAngle(units->iAngle);
      fsUnitsAngle(units->iAngle, cUnit);
    }
  } // In a hyperbolic orbit MeanL is represented as an area in radians
}

void WriteBaryEccA(BODY *body, CONTROL *control, OUTPUT *output,
                    SYSTEM *system, UNITS *units, UPDATE *update, int iBody,
                    double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dBaryEccA;

  if (output->bDoNeg[iBody]) {
    *dTmp *= output->dNeg;
    strcpy(cUnit, output->cNeg);
  } else {
    *dTmp /= fdUnitsAngle(units->iAngle);
    fsUnitsAngle(units->iAngle, cUnit);
  }
}

void WriteBaryHypA(BODY *body, CONTROL *control, OUTPUT *output,
                    SYSTEM *system, UNITS *units, UPDATE *update, int iBody,
                    double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dBaryHypA;
  // Do not convert to degrees
  // Hyperbolic Anomaly is a ratio of areas represented only in radians
}

//Other Barycentric variable Write functions below

void WriteBaryMu(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS
               *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  *dTmp = body[iBody].dBaryMu;

  if (output->bDoNeg[iBody]) {
    *dTmp *= output->dNeg;
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp /= fdUnitsMass(units->iMass); //MUST CHANGE UNITS HERE!!!
    fsUnitsMass(units->iMass,cUnit);
  }
}

void WriteBaryEccSq(BODY *body, CONTROL *control, OUTPUT *output,
                            SYSTEM *system, UNITS *units, UPDATE *update,
                            int iBody, double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dBaryEccSq;
}

void WriteBaryMeanMotion(BODY *body, CONTROL *control, OUTPUT *output,
                        SYSTEM *system, UNITS *units, UPDATE *update, int iBody,
                        double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dBaryMeanMotion;

  if (output->bDoNeg[iBody]) {
    *dTmp *= output->dNeg;
    strcpy(cUnit, output->cNeg);
  } else {
    *dTmp *= fdUnitsTime(units->iTime);
    fsUnitsRate(units->iTime, cUnit);
  }  
}

void WriteBaryOrbPeriod(BODY *body, CONTROL *control, OUTPUT *output,
                        SYSTEM *system, UNITS *units, UPDATE *update, int iBody,
                        double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dBaryOrbPeriod;

  if (output->bDoNeg[iBody]) {
    *dTmp *= output->dNeg;
    strcpy(cUnit, output->cNeg);
  } else {
    *dTmp *= fdUnitsTime(units->iTime);
    fsUnitsRate(units->iTime, cUnit);
  }
}

void WriteBarySinc(BODY *body, CONTROL *control, OUTPUT *output,
                            SYSTEM *system, UNITS *units, UPDATE *update,
                            int iBody, double *dTmp, char cUnit[]) {
  *dTmp = body[iBody].dBarySinc;
}



void InitializeOutputSpiNBody(OUTPUT *output, fnWriteOutput fnWrite[]) {
  // Output example for dPositionX variable
  // XXX All of these should be deprecated so that it doesn't matter if the user
  // calls DistOrb or SpiNBody

  // HelioCart values 


  sprintf(output[OUT_HELIOPOSX].cName, "HelioPosX");
  sprintf(output[OUT_HELIOPOSX].cDescr,
          "Body's x position where origin is centered at the primary mass.");
  // sprintf(output[OUT_HELIOPOSX].cNeg," ");
  output[OUT_HELIOPOSX].bNeg = 0;
  // output[OUT_HELIOPOSX].dNeg = 1;
  output[OUT_HELIOPOSX].iNum       = 1;
  output[OUT_HELIOPOSX].iModuleBit = SPINBODY;
  fnWrite[OUT_HELIOPOSX]           = &WriteHelioPosX;

  sprintf(output[OUT_HELIOPOSY].cName, "HelioPosY");
  sprintf(output[OUT_HELIOPOSY].cDescr,
          "Body's y position where origin is centered at the primary mass.");
  // sprintf(output[OUT_HELIOPOSY].cNeg," ");
  output[OUT_HELIOPOSY].bNeg = 0;
  // output[OUT_HELIOPOSY].dNeg = 1;
  output[OUT_HELIOPOSY].iNum       = 1;
  output[OUT_HELIOPOSY].iModuleBit = SPINBODY;
  fnWrite[OUT_HELIOPOSY]           = &WriteHelioPosY;

  sprintf(output[OUT_HELIOPOSZ].cName, "HelioPosZ");
  sprintf(output[OUT_HELIOPOSZ].cDescr,
          "Body's z position where origin is centered at the primary mass.");
  // sprintf(output[OUT_HELIOPOSZ].cNeg," ");
  output[OUT_HELIOPOSZ].bNeg = 0;
  // output[OUT_HELIOPOSZ].dNeg = 1;
  output[OUT_HELIOPOSZ].iNum       = 1;
  output[OUT_HELIOPOSZ].iModuleBit = SPINBODY;
  fnWrite[OUT_HELIOPOSZ]           = &WriteHelioPosZ;

  sprintf(output[OUT_HELIOVELX].cName, "HelioVelX");
  sprintf(output[OUT_HELIOVELX].cDescr, 
          "Body's x velocity where origin is centered at the primary mass.");
  // sprintf(output[OUT_HELIOVELX].cNeg," ");
  output[OUT_HELIOVELX].bNeg = 0;
  // output[OUT_HELIOVELX].dNeg = 1;
  output[OUT_HELIOVELX].iNum       = 1;
  output[OUT_HELIOVELX].iModuleBit = SPINBODY;
  fnWrite[OUT_HELIOVELX]           = &WriteHelioVelX;

  sprintf(output[OUT_HELIOVELY].cName, "HelioVelY");
  sprintf(output[OUT_HELIOVELY].cDescr, 
          "Body's y velocity where origin is centered at the primary mass.");
  // sprintf(output[OUT_HELIOVELY].cNeg," ");
  output[OUT_HELIOVELY].bNeg = 0;
  // output[OUT_HELIOVELY].dNeg = 1;
  output[OUT_HELIOVELY].iNum       = 1;
  output[OUT_HELIOVELY].iModuleBit = SPINBODY;
  fnWrite[OUT_HELIOVELY]           = &WriteHelioVelY;

  sprintf(output[OUT_HELIOVELZ].cName, "HelioVelZ");
  sprintf(output[OUT_HELIOVELZ].cDescr, 
          "Body's z velocity where origin is centered at the primary mass.");
  // sprintf(output[OUT_HELIOVELZ].cNeg," ");
  output[OUT_HELIOVELZ].bNeg = 0;
  // output[OUT_HELIOVELZ].dNeg = 1;
  output[OUT_HELIOVELZ].iNum       = 1;
  output[OUT_HELIOVELZ].iModuleBit = SPINBODY;
  fnWrite[OUT_HELIOVELZ]           = &WriteHelioVelZ;

  // HelioOrbElems values 

  sprintf(output[OUT_HELIOSEMI].cName, "HelioSemi");
  sprintf(output[OUT_HELIOSEMI].cDescr, 
          "Body's heliocentric semi-major axis where origin is centered at the primary mass.");
  sprintf(output[OUT_HELIOSEMI].cNeg, "AU");
  output[OUT_HELIOSEMI].bNeg       = 1;
  output[OUT_HELIOSEMI].dNeg       = 1. / AUM;
  output[OUT_HELIOSEMI].iNum       = 1;
  output[OUT_HELIOSEMI].iModuleBit = SPINBODY;
  fnWrite[OUT_HELIOSEMI]           = &WriteHelioSemi;

  sprintf(output[OUT_HELIOECC].cName, "HelioEcc");
  sprintf(output[OUT_HELIOECC].cDescr, 
          "Body's heliocentric eccentricity where the origin is centered at the primary mass.");
  output[OUT_HELIOECC].bNeg       = 0;
  output[OUT_HELIOECC].iNum       = 1;
  output[OUT_HELIOECC].iModuleBit = SPINBODY;
  fnWrite[OUT_HELIOECC]           = &WriteHelioEcc;
  
  sprintf(output[OUT_HELIOINC].cName, "HelioInc");
  sprintf(output[OUT_HELIOINC].cDescr, 
          "Body's heliocentric inclination where origin is centered at the primary mass.");
  sprintf(output[OUT_HELIOINC].cNeg, "Deg");
  output[OUT_HELIOINC].bNeg       = 1;
  output[OUT_HELIOINC].dNeg       = 1. / DEGRAD;
  output[OUT_HELIOINC].iNum       = 1;
  output[OUT_HELIOINC].iModuleBit = SPINBODY;
  fnWrite[OUT_HELIOINC]           = &WriteHelioInc;

  sprintf(output[OUT_HELIOLONGA].cName, "HelioLongA");
  sprintf(output[OUT_HELIOLONGA].cDescr, 
          "Body's heliocentric longitude of ascending node where origin is centered at the primary mass.");
  sprintf(output[OUT_HELIOLONGA].cNeg, "Deg");
  output[OUT_HELIOLONGA].bNeg       = 1;
  output[OUT_HELIOLONGA].dNeg       = 1. / DEGRAD;
  output[OUT_HELIOLONGA].iNum       = 1;
  output[OUT_HELIOLONGA].iModuleBit = SPINBODY;
  fnWrite[OUT_HELIOLONGA]           = &WriteHelioLongA;

  sprintf(output[OUT_HELIOARGP].cName, "HelioArgP");
  sprintf(output[OUT_HELIOARGP].cDescr, "The body's heliocentric Argument of Pericenter.");
  sprintf(output[OUT_HELIOARGP].cNeg, "Deg");
  output[OUT_HELIOARGP].bNeg       = 1;
  output[OUT_HELIOARGP].dNeg       = 1. / DEGRAD;
  output[OUT_HELIOARGP].iNum       = 1;
  output[OUT_HELIOARGP].iModuleBit = SPINBODY;
  fnWrite[OUT_HELIOARGP]           = &WriteHelioArgP;

  sprintf(output[OUT_HELIOLONGP].cName, "HelioLongP");
  sprintf(output[OUT_HELIOLONGP].cDescr, 
          "Body's  heliocntric longitude of pericenter where origin is centered at the primary mass.");
  sprintf(output[OUT_HELIOLONGP].cNeg, "Deg");
  output[OUT_HELIOLONGP].bNeg       = 1;
  output[OUT_HELIOLONGP].dNeg       = 1. / DEGRAD;
  output[OUT_HELIOLONGP].iNum       = 1;
  output[OUT_HELIOLONGP].iModuleBit = SPINBODY;
  fnWrite[OUT_HELIOLONGP]           = &WriteHelioLongP;

  sprintf(output[OUT_HELIOMEANA].cName, "HelioMeanA");
  sprintf(output[OUT_HELIOMEANA].cDescr, 
          "Body's heliocntric mean anamoly where origin is centered at the primary mass.");
  sprintf(output[OUT_HELIOMEANA].cNeg, "Deg");
  output[OUT_HELIOMEANA].bNeg       = 1;
  output[OUT_HELIOMEANA].dNeg       = 1. / DEGRAD;
  output[OUT_HELIOMEANA].iNum       = 1;
  output[OUT_HELIOMEANA].iModuleBit = SPINBODY;
  fnWrite[OUT_HELIOMEANA]           = &WriteHelioMeanA;

  sprintf(output[OUT_HELIOMEANL].cName, "HelioMeanL");
  sprintf(output[OUT_HELIOMEANL].cDescr, 
          "Body's heliocentric Mean Longitude where origin is centered at the primary mass.");
  sprintf(output[OUT_HELIOMEANL].cNeg, "Deg");
  output[OUT_HELIOMEANL].bNeg       = 1;
  output[OUT_HELIOMEANL].dNeg       = 1. / DEGRAD;
  output[OUT_HELIOMEANL].iNum       = 1;
  output[OUT_HELIOMEANL].iModuleBit = SPINBODY;
  fnWrite[OUT_HELIOMEANL]           = &WriteHelioMeanL;


  sprintf(output[OUT_HELIOECCA].cName, "HelioEccA");
  sprintf(output[OUT_HELIOECCA].cDescr, 
          "Body's heliocentric Eccentric Anomaly where origin is centered at the primary mass.");
  sprintf(output[OUT_HELIOECCA].cNeg, "Deg");
  output[OUT_HELIOECCA].bNeg       = 1;
  output[OUT_HELIOECCA].dNeg       = 1. / DEGRAD;
  output[OUT_HELIOECCA].iNum       = 1;
  output[OUT_HELIOECCA].iModuleBit = SPINBODY;
  fnWrite[OUT_HELIOECCA]           = &WriteHelioEccA;

  sprintf(output[OUT_HELIOHYPA].cName, "HelioHypA");
  sprintf(output[OUT_HELIOHYPA].cDescr, 
          "Body's heliocentric Hyperbolic Anomaly where origin is centered at the primary mass.");
  sprintf(output[OUT_HELIOHYPA].cNeg, "Deg");
  output[OUT_HELIOHYPA].bNeg       = 1;
  output[OUT_HELIOHYPA].dNeg       = 1. / DEGRAD;
  output[OUT_HELIOHYPA].iNum       = 1;
  output[OUT_HELIOHYPA].iModuleBit = SPINBODY;
  fnWrite[OUT_HELIOHYPA]           = &WriteHelioHypA;
  


  // BaryCart values 


  sprintf(output[OUT_BARYPOSX].cName, "BaryPosX");
  sprintf(output[OUT_BARYPOSX].cDescr,
          "Body's x position where origin is centered at the system's barycenter.");
  // sprintf(output[OUT_BARYPOSX].cNeg," ");
  output[OUT_BARYPOSX].bNeg = 0;
  // output[OUT_BARYPOSX].dNeg = 1;
  output[OUT_BARYPOSX].iNum       = 1;
  output[OUT_BARYPOSX].iModuleBit = SPINBODY;
  fnWrite[OUT_BARYPOSX]           = &WriteBaryPosX;

  sprintf(output[OUT_BARYPOSY].cName, "BaryPosY");
  sprintf(output[OUT_BARYPOSY].cDescr,
          "Body's y position where origin is centered at the system's barycenter.");
  // sprintf(output[OUT_BARYPOSY].cNeg," ");
  output[OUT_BARYPOSY].bNeg = 0;
  // output[OUT_BARYPOSY].dNeg = 1;
  output[OUT_BARYPOSY].iNum       = 1;
  output[OUT_BARYPOSY].iModuleBit = SPINBODY;
  fnWrite[OUT_BARYPOSY]           = &WriteBaryPosY;

  sprintf(output[OUT_BARYPOSZ].cName, "BaryPosZ");
  sprintf(output[OUT_BARYPOSZ].cDescr,
          "Body's z position where origin is centered at the system's barycenter.");
  // sprintf(output[OUT_BARYPOSZ].cNeg," ");
  output[OUT_BARYPOSZ].bNeg = 0;
  // output[OUT_BARYPOSZ].dNeg = 1;
  output[OUT_BARYPOSZ].iNum       = 1;
  output[OUT_BARYPOSZ].iModuleBit = SPINBODY;
  fnWrite[OUT_BARYPOSZ]           = &WriteBaryPosZ;

  sprintf(output[OUT_BARYVELX].cName, "BaryVelX");
  sprintf(output[OUT_BARYVELX].cDescr, 
          "Body's x velocity where origin is centered at the system's barycenter.");
  // sprintf(output[OUT_BARYVELX].cNeg," ");
  output[OUT_BARYVELX].bNeg = 0;
  // output[OUT_BARYVELX].dNeg = 1;
  output[OUT_BARYVELX].iNum       = 1;
  output[OUT_BARYVELX].iModuleBit = SPINBODY;
  fnWrite[OUT_BARYVELX]           = &WriteBaryVelX;

  sprintf(output[OUT_BARYVELY].cName, "BaryVelY");
  sprintf(output[OUT_BARYVELY].cDescr, 
          "Body's y velocity where origin is centered at the system's barycenter.");
  // sprintf(output[OUT_BARYVELY].cNeg," ");
  output[OUT_BARYVELY].bNeg = 0;
  // output[OUT_BARYVELY].dNeg = 1;
  output[OUT_BARYVELY].iNum       = 1;
  output[OUT_BARYVELY].iModuleBit = SPINBODY;
  fnWrite[OUT_BARYVELY]           = &WriteBaryVelY;

  sprintf(output[OUT_BARYVELZ].cName, "BaryVelZ");
  sprintf(output[OUT_BARYVELZ].cDescr, 
          "Body's z velocity where origin is centered at the system's barycenter.");
  // sprintf(output[OUT_BARYVELZ].cNeg," ");
  output[OUT_BARYVELZ].bNeg = 0;
  // output[OUT_BARYVELZ].dNeg = 1;
  output[OUT_BARYVELZ].iNum       = 1;
  output[OUT_BARYVELZ].iModuleBit = SPINBODY;
  fnWrite[OUT_BARYVELZ]           = &WriteBaryVelZ;

  // BaryOrbElems values 

  sprintf(output[OUT_BARYSEMI].cName, "BarySemi");
  sprintf(output[OUT_BARYSEMI].cDescr, 
          "Body's semi-major axis where origin is centered at the system's barycenter.");
  sprintf(output[OUT_BARYSEMI].cNeg, "AU");
  output[OUT_BARYSEMI].bNeg       = 1;
  output[OUT_BARYSEMI].dNeg       = 1. / AUM;
  output[OUT_BARYSEMI].iNum       = 1;
  output[OUT_BARYSEMI].iModuleBit = SPINBODY;
  fnWrite[OUT_BARYSEMI]           = &WriteBarySemi;

  sprintf(output[OUT_BARYECC].cName, "BaryEcc");
  sprintf(output[OUT_BARYECC].cDescr, 
          "Body's eccentricity where the origin is centered at the system's barycenter.");
  output[OUT_BARYECC].bNeg       = 0;
  output[OUT_BARYECC].iNum       = 1;
  output[OUT_BARYECC].iModuleBit = SPINBODY;
  fnWrite[OUT_BARYECC]           = &WriteBaryEcc;

  sprintf(output[OUT_BARYINC].cName, "BaryInc");
  sprintf(output[OUT_BARYINC].cDescr, 
          "Body's inclination where origin is centered at the system's barycenter.");
  sprintf(output[OUT_BARYINC].cNeg, "Deg");
  output[OUT_BARYINC].bNeg       = 1;
  output[OUT_BARYINC].dNeg       = 1. / DEGRAD;
  output[OUT_BARYINC].iNum       = 1;
  output[OUT_BARYINC].iModuleBit = SPINBODY;
  fnWrite[OUT_BARYINC]           = &WriteBaryInc;

  sprintf(output[OUT_BARYLONGA].cName, "BaryLongA");
  sprintf(output[OUT_BARYLONGA].cDescr, 
          "Body's longitude of ascending node where origin is centered at the system's barycenter.");
  sprintf(output[OUT_BARYLONGA].cNeg, "Deg");
  output[OUT_BARYLONGA].bNeg       = 1;
  output[OUT_BARYLONGA].dNeg       = 1. / DEGRAD;
  output[OUT_BARYLONGA].iNum       = 1;
  output[OUT_BARYLONGA].iModuleBit = SPINBODY;
  fnWrite[OUT_BARYLONGA]           = &WriteBaryLongA;

  sprintf(output[OUT_BARYARGP].cName, "BaryArgP");
  sprintf(output[OUT_BARYARGP].cDescr, "The body's barycentric Argument of Pericenter.");
  sprintf(output[OUT_BARYARGP].cNeg, "Deg");
  output[OUT_BARYARGP].bNeg       = 1;
  output[OUT_BARYARGP].dNeg       = 1. / DEGRAD;
  output[OUT_BARYARGP].iNum       = 1;
  output[OUT_BARYARGP].iModuleBit = SPINBODY;
  fnWrite[OUT_BARYARGP]           = &WriteBaryArgP;

  sprintf(output[OUT_BARYLONGP].cName, "BaryLongP");
  sprintf(output[OUT_BARYLONGP].cDescr, 
          "Body's longitude of pericenter where origin is centered at the system's barycenter.");
  sprintf(output[OUT_BARYLONGP].cNeg, "Deg");
  output[OUT_BARYLONGP].bNeg       = 1;
  output[OUT_BARYLONGP].dNeg       = 1. / DEGRAD;
  output[OUT_BARYLONGP].iNum       = 1;
  output[OUT_BARYLONGP].iModuleBit = SPINBODY;
  fnWrite[OUT_BARYLONGP]           = &WriteBaryLongP;

  sprintf(output[OUT_BARYMEANA].cName, "BaryMeanA");
  sprintf(output[OUT_BARYMEANA].cDescr, 
          "Body's mean anamoly where origin is centered at the system's barycenter.");
  sprintf(output[OUT_BARYMEANA].cNeg, "Deg");
  output[OUT_BARYMEANA].bNeg       = 1;
  output[OUT_BARYMEANA].dNeg       = 1. / DEGRAD;
  output[OUT_BARYMEANA].iNum       = 1;
  output[OUT_BARYMEANA].iModuleBit = SPINBODY;
  fnWrite[OUT_BARYMEANA]           = &WriteBaryMeanA;

  sprintf(output[OUT_BARYMEANL].cName, "BaryMeanL");
  sprintf(output[OUT_BARYMEANL].cDescr, 
          "Body's barycentric Mean Longitude where origin is centered at the system's barycenter.");
  sprintf(output[OUT_BARYMEANL].cNeg, "Deg");
  output[OUT_BARYMEANL].bNeg       = 1;
  output[OUT_BARYMEANL].dNeg       = 1. / DEGRAD;
  output[OUT_BARYMEANL].iNum       = 1;
  output[OUT_BARYMEANL].iModuleBit = SPINBODY;
  fnWrite[OUT_BARYMEANL]           = &WriteBaryMeanL;

  sprintf(output[OUT_BARYECCA].cName, "BaryEccA");
  sprintf(output[OUT_BARYECCA].cDescr, 
          "Body's barycentric Eccentric Anomaly where origin is centered at the system's barycenter");
  sprintf(output[OUT_BARYECCA].cNeg, "Deg");
  output[OUT_BARYECCA].bNeg       = 1;
  output[OUT_BARYECCA].dNeg       = 1. / DEGRAD;
  output[OUT_BARYECCA].iNum       = 1;
  output[OUT_BARYECCA].iModuleBit = SPINBODY;
  fnWrite[OUT_BARYECCA]           = &WriteBaryEccA;

  sprintf(output[OUT_BARYHYPA].cName, "BaryHypA");
  sprintf(output[OUT_BARYHYPA].cDescr, 
          "Body's barycentric Hyperbolic Anomaly where origin is centered at the system's barycenter.");
  sprintf(output[OUT_BARYHYPA].cNeg, "Deg");
  output[OUT_BARYHYPA].bNeg       = 1;
  output[OUT_BARYHYPA].dNeg       = 1. / DEGRAD;
  output[OUT_BARYHYPA].iNum       = 1;
  output[OUT_BARYHYPA].iModuleBit = SPINBODY;
  fnWrite[OUT_BARYHYPA]           = &WriteBaryHypA;

  //Other Barycentric variables
  //body[iBody].dBaryMu
  //body[iBody].dBaryEccSq
  //body[iBody].dBaryArgP
  //body[iBody].dBaryEccA
  //body[iBody].dBaryOrbPeriod


  sprintf(output[OUT_BARYMU].cName, "BaryMu");
  sprintf(output[OUT_BARYMU].cDescr, "The system's Barycenter mass.");
  sprintf(output[OUT_BARYMU].cNeg, "Mearth");
  output[OUT_BARYMU].bNeg         = 1;
  output[OUT_BARYMU].dNeg         = 1./ MEARTH; // MUST CHANGE UNITS!!
  output[OUT_BARYMU].iNum         = 1;
  output[OUT_BARYMU].iModuleBit   = SPINBODY;
  fnWrite[OUT_BARYMU]             = &WriteBaryMu;

  sprintf(output[OUT_BARYECCSQ].cName, "BaryEccSq");
  sprintf(output[OUT_BARYECCSQ].cDescr, "The body's barycentric eccentricity squared.");
  output[OUT_BARYECCSQ].bNeg       = 0;
  output[OUT_BARYECCSQ].iNum       = 1;
  output[OUT_BARYECCSQ].iModuleBit = SPINBODY;
  fnWrite[OUT_BARYECCSQ]           = &WriteBaryEccSq;

  sprintf(output[OUT_BARYMEANMOTION].cName, "BaryMeanMotion");
  sprintf(output[OUT_BARYMEANMOTION].cDescr, "The body's Mean Motion with respect to the system's barycenter.");
  sprintf(output[OUT_BARYMEANMOTION].cNeg, "/day");
  output[OUT_BARYMEANMOTION].bNeg       = 1;
  output[OUT_BARYMEANMOTION].dNeg       = DAYSEC;
  output[OUT_BARYMEANMOTION].iNum       = 1;
  output[OUT_BARYMEANMOTION].iModuleBit = SPINBODY;
  fnWrite[OUT_BARYMEANMOTION]           = &WriteBaryMeanMotion;

  sprintf(output[OUT_BARYORBPERIOD].cName, "BaryOrbPeriod");
  sprintf(output[OUT_BARYORBPERIOD].cDescr, "The body's Orbital Period with respect to the system's barycenter.");
  sprintf(output[OUT_BARYORBPERIOD].cNeg, "days");
  output[OUT_BARYORBPERIOD].bNeg        = 1;
  output[OUT_BARYORBPERIOD].dNeg        = 1. / DAYSEC;
  output[OUT_BARYORBPERIOD].iNum        = 1;
  output[OUT_BARYORBPERIOD].iModuleBit = SPINBODY;
  fnWrite[OUT_BARYORBPERIOD]            = &WriteBaryOrbPeriod;

  sprintf(output[OUT_BARYSINC].cName, "BarySinc");
  sprintf(output[OUT_BARYSINC].cDescr, "Sin(BaryInc / 2.0)");
  output[OUT_BARYSINC].bNeg           = 1;
  output[OUT_BARYSINC].iNum           = 1;
  output[OUT_BARYSINC].iModuleBit     = SPINBODY;
  fnWrite[OUT_BARYSINC]               = &WriteBarySinc;

}


//============================ End Writing Functions ===========================

void fnForceBehaviorSpiNBody(BODY *body, MODULE *module, EVOLVE *evolve, IO *io,
                             SYSTEM *system, UPDATE *update,
                             fnUpdateVariable ***fnUpdate, int iBody,
                             int iModule) {
}

void PropsAuxSpiNBody(BODY *body, EVOLVE *evolve, IO *io, UPDATE *update,
                      int iBody) {
  int jBody, iNumBodies;
  double DistanceX, DistanceY, DistanceZ, Distance3;

  iNumBodies      = evolve->iNumBodies;
  body[iBody].dGM = BIGG * body[iBody].dMass;

  for (jBody = 0; jBody < iNumBodies; jBody++) {
    // Calculate the cube of the distance to each perturbing body. Used in Vx,
    // Vy, and Vz calculations.
    if (iBody < jBody) {
      //(body[jBody].dPositionY-body[iaBody[0]].dPositionY)/body[iaBody[0]].dDistance3[jBody];
      DistanceX = body[jBody].dPositionX - body[iBody].dPositionX;
      DistanceY = body[jBody].dPositionY - body[iBody].dPositionY;
      DistanceZ = body[jBody].dPositionZ - body[iBody].dPositionZ;
      /* body[iBody].dDistance3[jBody] = sqrt(DistanceX*DistanceX
            + DistanceY*DistanceY
            + DistanceZ*DistanceZ); */
      Distance3 = sqrt(DistanceX * DistanceX + DistanceY * DistanceY +
                       DistanceZ * DistanceZ);
      // body[iBody].dDistance3[jBody] =
      // 1/(body[iBody].dDistance3[jBody]*body[iBody].dDistance3[jBody]*body[iBody].dDistance3[jBody]);
      Distance3                     = 1 / (Distance3 * Distance3 * Distance3);
      body[iBody].dDistanceX[jBody] = DistanceX * Distance3;
      body[iBody].dDistanceY[jBody] = DistanceY * Distance3;
      body[iBody].dDistanceZ[jBody] = DistanceZ * Distance3;

      // body[jBody].dDistance3[iBody] = body[iBody].dDistance3[jBody];
      body[jBody].dDistanceX[iBody] = -body[iBody].dDistanceX[jBody];
      body[jBody].dDistanceY[iBody] = -body[iBody].dDistanceY[jBody];
      body[jBody].dDistanceZ[iBody] = -body[iBody].dDistanceZ[jBody];
    }
  }
}

//========================= Finalize Variable Functions ========================
void FinalizeUpdateVelXSpiNBody(BODY *body, UPDATE *update, int *iEqn, int iVar,
                                int iBody, int iFoo) {
  update[iBody].iaModule[iVar][*iEqn] = SPINBODY;
  update[iBody].iNumVelX              = (*iEqn)++;
}

void FinalizeUpdateVelYSpiNBody(BODY *body, UPDATE *update, int *iEqn, int iVar,
                                int iBody, int iFoo) {
  update[iBody].iaModule[iVar][*iEqn] = SPINBODY;
  update[iBody].iNumVelY              = (*iEqn)++;
}

void FinalizeUpdateVelZSpiNBody(BODY *body, UPDATE *update, int *iEqn, int iVar,
                                int iBody, int iFoo) {
  update[iBody].iaModule[iVar][*iEqn] = SPINBODY;
  update[iBody].iNumVelZ              = (*iEqn)++;
}

void FinalizeUpdatePositionXSpiNBody(BODY *body, UPDATE *update, int *iEqn,
                                     int iVar, int iBody, int iFoo) {
  update[iBody].iaModule[iVar][*iEqn] = SPINBODY;
  update[iBody].iNumPositionX         = (*iEqn)++;
}

void FinalizeUpdatePositionYSpiNBody(BODY *body, UPDATE *update, int *iEqn,
                                     int iVar, int iBody, int iFoo) {
  update[iBody].iaModule[iVar][*iEqn] = SPINBODY;
  update[iBody].iNumPositionY         = (*iEqn)++;
}

void FinalizeUpdatePositionZSpiNBody(BODY *body, UPDATE *update, int *iEqn,
                                     int iVar, int iBody, int iFoo) {
  update[iBody].iaModule[iVar][*iEqn] = SPINBODY;
  update[iBody].iNumPositionZ         = (*iEqn)++;
}
//======================= End Finalize Variable Functions ======================

//================================ Log Functions ===============================

void LogBodySpiNBody(BODY *body, CONTROL *control, OUTPUT *output,
                     SYSTEM *system, UPDATE *update, fnWriteOutput fnWrite[],
                     FILE *fp, int iBody) {
  int iOut;
  fprintf(fp, "----- SPINBODY PARAMETERS (%s)------\n", body[iBody].cName);

  for (iOut = OUTSTARTSPINBODY; iOut < OUTENDSPINBODY; iOut++) {
    if (output[iOut].iNum > 0) {
      WriteLogEntry(body, control, &output[iOut], system, update, fnWrite[iOut],
                    fp, iBody);
    }
  }
}

void LogSpiNBody(BODY *body, CONTROL *control, OUTPUT *output, SYSTEM *system,
                 UPDATE *update, fnWriteOutput fnWrite[], FILE *fp) {
  int iOut;
  // I don't think this is called anywhere
  fprintf(fp, "\n----- SPINBODY PARAMETERS ------\n");
  for (iOut = OUTSTARTSPINBODY; iOut < OUTBODYSTARTSPINBODY; iOut++) {
    if (output[iOut].iNum > 0) {
      WriteLogEntry(body, control, &output[iOut], system, update, fnWrite[iOut],
                    fp, 0);
    }
  }
}

//============================= End Log Functions ==============================

// Add Module Function
void AddModuleSpiNBody(CONTROL *control, MODULE *module, int iBody,
                       int iModule) {

  module->iaModule[iBody][iModule] = SPINBODY; // Name

  // Halts
  module->fnCountHalts[iBody][iModule] = &CountHaltsSpiNBody;
  module->fnVerifyHalt[iBody][iModule] = &VerifyHaltSpiNBody;

  module->fnLogBody[iBody][iModule]           = &LogBodySpiNBody;
  module->fnReadOptions[iBody][iModule]       = &ReadOptionsSpiNBody;
  module->fnVerify[iBody][iModule]            = &VerifySpiNBody;
  module->fnAssignDerivatives[iBody][iModule] = &AssignSpiNBodyDerivatives;
  module->fnNullDerivatives[iBody][iModule]   = &NullSpiNBodyDerivatives;

  module->fnInitializeBody[iBody][iModule]   = &InitializeBodySpiNBody;
  module->fnInitializeUpdate[iBody][iModule] = &InitializeUpdateSpiNBody;
  module->fnInitializeOutput[iBody][iModule] = &InitializeOutputSpiNBody;
  module->fnInitializeUpdateTmpBody[iBody][iModule] =
        &InitializeUpdateTmpBodySpiNBody;

  // Primary Variable Finalizations
  module->fnFinalizeUpdateVelX[iBody][iModule] = &FinalizeUpdateVelXSpiNBody;
  module->fnFinalizeUpdateVelY[iBody][iModule] = &FinalizeUpdateVelYSpiNBody;
  module->fnFinalizeUpdateVelZ[iBody][iModule] = &FinalizeUpdateVelZSpiNBody;
  module->fnFinalizeUpdatePositionX[iBody][iModule] =
        &FinalizeUpdatePositionXSpiNBody;
  module->fnFinalizeUpdatePositionY[iBody][iModule] =
        &FinalizeUpdatePositionYSpiNBody;
  module->fnFinalizeUpdatePositionZ[iBody][iModule] =
        &FinalizeUpdatePositionZSpiNBody;
}

//============================= SpiNBody Functions =============================

double fdDPositionXDt(BODY *body, SYSTEM *system, int *iaBody) {
  return body[iaBody[0]].dVelX;
}

double fdDPositionYDt(BODY *body, SYSTEM *system, int *iaBody) {
  return body[iaBody[0]].dVelY;
}

double fdDPositionZDt(BODY *body, SYSTEM *system, int *iaBody) {
  return body[iaBody[0]].dVelZ;
}

double fdDVelXDt(BODY *body, SYSTEM *system, int *iaBody) {
  double dSumX = 0; // Double used to calculate the net perturbation
  int jBody, iGravPerts;
  iGravPerts = body[iaBody[0]].iGravPertsSpiNBody;

  for (jBody = 0; jBody < iGravPerts; jBody++) {
    if (iaBody[0] != jBody) {
      // dSumX = dSumX +
      // BIGG*body[jBody].dMass*(body[jBody].dPositionX-body[iaBody[0]].dPositionX)/body[iaBody[0]].dDistance3[jBody];
      dSumX = dSumX + body[jBody].dGM * body[iaBody[0]].dDistanceX[jBody];
    }
  }

  return dSumX;
}

double fdDVelYDt(BODY *body, SYSTEM *system, int *iaBody) {
  double dSumY = 0; // Double used to calculate the net perturbation
  int jBody, iGravPerts;
  iGravPerts = body[iaBody[0]].iGravPertsSpiNBody;

  for (jBody = 0; jBody < iGravPerts; jBody++) {
    if (iaBody[0] != jBody) {
      // dSumY = dSumY +
      // BIGG*body[jBody].dMass*(body[jBody].dPositionY-body[iaBody[0]].dPositionY)/body[iaBody[0]].dDistance3[jBody];
      dSumY = dSumY + body[jBody].dGM * body[iaBody[0]].dDistanceY[jBody];
    }
  }

  return dSumY;
}

double fdDVelZDt(BODY *body, SYSTEM *system, int *iaBody) {
  double dSumZ = 0; // Double used to calculate the net perturbation
  int jBody, iGravPerts;
  iGravPerts = body[iaBody[0]].iGravPertsSpiNBody;

  for (jBody = 0; jBody < iGravPerts; jBody++) {
    if (iaBody[0] != jBody) {
      // dSumZ = dSumZ +
      // BIGG*body[jBody].dMass*(body[jBody].dPositionZ-body[iaBody[0]].dPositionZ)/body[iaBody[0]].dDistance3[jBody];
      dSumZ = dSumZ + body[jBody].dGM * body[iaBody[0]].dDistanceZ[jBody];
    }
  }

  return dSumZ;
}
//========================== End SpiNBody Functions ============================
