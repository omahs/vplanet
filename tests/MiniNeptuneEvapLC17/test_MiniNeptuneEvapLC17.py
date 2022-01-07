from benchmark import Benchmark, benchmark 
import astropy.units as u 
import pytest 
 
@benchmark( 
   { 
       "log.initial.system.Age": {"value": 3.155760e+13, "unit": u.sec}, 
       "log.initial.system.Time": {"value": 0.000000, "unit": u.sec}, 
       "log.initial.system.TotAngMom": {"value": 1.830068e+40, "unit": (u.kg * u.m ** 2) / u.sec}, 
       "log.initial.system.TotEnergy": {"value": -2.482440e+43, "unit": u.Joule}, 
       "log.initial.system.PotEnergy": {"value": -2.482440e+43, "unit": u.Joule}, 
       "log.initial.system.KinEnergy": {"value": 5.347271e+34, "unit": u.Joule}, 
       "log.initial.system.DeltaTime": {"value": 0.000000, "unit": u.sec}, 
       "log.initial.star.Mass": {"value": 1.988416e+30, "unit": u.kg}, 
       "log.initial.star.Radius": {"value": 6.378100e+06, "unit": u.m}, 
       "log.initial.star.RadGyra": {"value": 0.500000}, 
       "log.initial.star.RotAngMom": {"value": 1.470605e+39, "unit": (u.kg * u.m ** 2) / u.sec}, 
       "log.initial.star.RotVel": {"value": 463.828521, "unit": u.m / u.sec}, 
       "log.initial.star.BodyType": {"value": 0.000000}, 
       "log.initial.star.RotRate": {"value": 7.272205e-05, "unit": 1 / u.sec}, 
       "log.initial.star.RotPer": {"value": 8.640000e+04, "unit": u.sec}, 
       "log.initial.star.Density": {"value": 1.829552e+09, "unit": u.kg / u.m ** 3}, 
       "log.initial.star.HZLimitDryRunaway": {"value": 1.357831e+11, "unit": u.m}, 
       "log.initial.star.HZLimRecVenus": {"value": 1.118929e+11, "unit": u.m}, 
       "log.initial.star.HZLimRunaway": {"value": 1.461108e+11, "unit": u.m}, 
       "log.initial.star.HZLimMoistGreenhouse": {"value": 1.480517e+11, "unit": u.m}, 
       "log.initial.star.HZLimMaxGreenhouse": {"value": 2.509538e+11, "unit": u.m}, 
       "log.initial.star.HZLimEarlyMars": {"value": 2.738109e+11, "unit": u.m}, 
       "log.initial.star.Instellation": {"value": -1.000000, "unit": u.kg / u.sec ** 3}, 
       "log.initial.star.CriticalSemiMajorAxis": {"value": -1.000000, "unit": u.m}, 
       "log.initial.star.LXUVTot": {"value": 0.000400, "unit": u.LSUN}, 
       "log.initial.star.LostEnergy": {"value": 5.562685e-309, "unit": u.Joule}, 
       "log.initial.star.LostAngMom": {"value": 5.562685e-309, "unit": (u.kg * u.m ** 2) / u.sec}, 
       "log.initial.star.Luminosity": {"value": 1.000000, "unit": u.LSUN}, 
       "log.initial.star.LXUVStellar": {"value": 1.538400e+23, "unit": u.W}, 
       "log.initial.star.Temperature": {"value": 5778.000000, "unit": u.K}, 
       "log.initial.star.LXUVFrac": {"value": 0.000400}, 
       "log.initial.star.RossbyNumber": {"value": 0.078260}, 
       "log.initial.star.DRotPerDtStellar": {"value": 6.530034e-18}, 
       "log.initial.planet.Mass": {"value": 2.000000, "unit": u.Mearth}, 
       "log.initial.planet.Radius": {"value": 3.113121e+07, "unit": u.m}, 
       "log.initial.planet.RadGyra": {"value": 0.500000}, 
       "log.initial.planet.BodyType": {"value": 0.000000}, 
       "log.initial.planet.Density": {"value": 94.511932, "unit": u.kg / u.m ** 3}, 
       "log.initial.planet.HZLimitDryRunaway": {"value": 1.357831e+11, "unit": u.m}, 
       "log.initial.planet.HZLimRecVenus": {"value": 1.118929e+11, "unit": u.m}, 
       "log.initial.planet.HZLimRunaway": {"value": 1.461108e+11, "unit": u.m}, 
       "log.initial.planet.HZLimMoistGreenhouse": {"value": 1.480517e+11, "unit": u.m}, 
       "log.initial.planet.HZLimMaxGreenhouse": {"value": 2.509538e+11, "unit": u.m}, 
       "log.initial.planet.HZLimEarlyMars": {"value": 2.738109e+11, "unit": u.m}, 
       "log.initial.planet.Instellation": {"value": 1.367567e+05, "unit": u.kg / u.sec ** 3}, 
       "log.initial.planet.MeanMotion": {"value": 6.296062e-06, "unit": 1 / u.sec}, 
       "log.initial.planet.OrbPeriod": {"value": 9.979547e+05, "unit": u.sec}, 
       "log.initial.planet.SemiMajorAxis": {"value": 1.495979e+10, "unit": u.m}, 
       "log.initial.planet.LXUVTot": {"value": -1.000000, "unit": u.kg / u.sec ** 3}, 
       "log.initial.planet.SurfWaterMass": {"value": 0.000000, "unit": u.kg}, 
       "log.initial.planet.EnvelopeMass": {"value": 0.060000, "unit": u.Mearth}, 
       "log.initial.planet.OxygenMass": {"value": 0.000000, "unit": u.kg}, 
       "log.initial.planet.RGLimit": {"value": 1.400183e+11, "unit": u.m}, 
       "log.initial.planet.XO": {"value": 0.000000}, 
       "log.initial.planet.EtaO": {"value": 0.000000}, 
       "log.initial.planet.PlanetRadius": {"value": 4.880954, "unit": u.Rearth}, 
       "log.initial.planet.OxygenMantleMass": {"value": 0.000000, "unit": u.kg}, 
       "log.initial.planet.RadXUV": {"value": 4.880954, "unit": u.Rearth}, 
       "log.initial.planet.RadSolid": {"value": 7.606867e+06, "unit": u.m}, 
       "log.initial.planet.PresXUV": {"value": 5.000000}, 
       "log.initial.planet.ScaleHeight": {"value": 273.737851, "unit": u.km}, 
       "log.initial.planet.ThermTemp": {"value": 880.000000, "unit": u.K}, 
       "log.initial.planet.AtmGasConst": {"value": 4157.000000}, 
       "log.initial.planet.PresSurf": {"value": 6.585533, "unit": u.GPa}, 
       "log.initial.planet.DEnvMassDt": {"value": -8.619175e+08, "unit": u.kg / u.sec}, 
       "log.initial.planet.FXUV": {"value": 54.702677, "unit": u.W / u.m ** 2}, 
       "log.initial.planet.AtmXAbsEffH2O": {"value": 0.150000}, 
       "log.initial.planet.RocheRadius": {"value": 29.562809, "unit": u.Rearth}, 
       "log.initial.planet.BondiRadius": {"value": 7.899468e+08, "unit": u.m}, 
       "log.initial.planet.HEscapeRegime": {"value": 3.000000}, 
       "log.initial.planet.RRCriticalFlux": {"value": 2.366968, "unit": u.W / u.m ** 2}, 
       "log.initial.planet.KTide": {"value": 0.754594}, 
       "log.initial.planet.RGDuration": {"value": 0.00000e+00, "unit": u.yr}, 
       "log.final.system.Age": {"value": 3.471336e+14, "unit": u.sec}, 
       "log.final.system.Time": {"value": 3.155760e+14, "unit": u.sec}, 
       "log.final.system.TotAngMom": {"value": 1.798369e+40, "unit": (u.kg * u.m ** 2) / u.sec}, 
       "log.final.system.TotEnergy": {"value": -2.482440e+43, "unit": u.Joule}, 
       "log.final.system.PotEnergy": {"value": -2.482440e+43, "unit": u.Joule}, 
       "log.final.system.KinEnergy": {"value": 5.347270e+34, "unit": u.Joule}, 
       "log.final.system.DeltaTime": {"value": 7.123612e+10, "unit": u.sec}, 
       "log.final.star.Mass": {"value": 1.988416e+30, "unit": u.kg}, 
       "log.final.star.Radius": {"value": 6.378100e+06, "unit": u.m}, 
       "log.final.star.RadGyra": {"value": 0.500000}, 
       "log.final.star.RotAngMom": {"value": 1.470605e+39, "unit": (u.kg * u.m ** 2) / u.sec}, 
       "log.final.star.RotVel": {"value": 463.828510, "unit": u.m / u.sec}, 
       "log.final.star.BodyType": {"value": 0.000000}, 
       "log.final.star.RotRate": {"value": 7.272205e-05, "unit": 1 / u.sec}, 
       "log.final.star.RotPer": {"value": 8.640000e+04, "unit": u.sec}, 
       "log.final.star.Density": {"value": 1.829552e+09, "unit": u.kg / u.m ** 3}, 
       "log.final.star.HZLimitDryRunaway": {"value": 1.357831e+11, "unit": u.m}, 
       "log.final.star.HZLimRecVenus": {"value": 1.118929e+11, "unit": u.m}, 
       "log.final.star.HZLimRunaway": {"value": 1.461108e+11, "unit": u.m}, 
       "log.final.star.HZLimMoistGreenhouse": {"value": 1.480517e+11, "unit": u.m}, 
       "log.final.star.HZLimMaxGreenhouse": {"value": 2.509538e+11, "unit": u.m}, 
       "log.final.star.HZLimEarlyMars": {"value": 2.738109e+11, "unit": u.m}, 
       "log.final.star.Instellation": {"value": -1.000000, "unit": u.kg / u.sec ** 3}, 
       "log.final.star.CriticalSemiMajorAxis": {"value": -1.000000, "unit": u.m}, 
       "log.final.star.LXUVTot": {"value": 0.000400, "unit": u.LSUN}, 
       "log.final.star.LostEnergy": {"value": 2.550749e+27, "unit": u.Joule}, 
       "log.final.star.LostAngMom": {"value": 3.507532e+31, "unit": (u.kg * u.m ** 2) / u.sec}, 
       "log.final.star.Luminosity": {"value": 1.000000, "unit": u.LSUN}, 
       "log.final.star.LXUVStellar": {"value": 1.538400e+23, "unit": u.W}, 
       "log.final.star.Temperature": {"value": 5778.000000, "unit": u.K}, 
       "log.final.star.LXUVFrac": {"value": 0.000400}, 
       "log.final.star.RossbyNumber": {"value": 0.078260}, 
       "log.final.star.DRotPerDtStellar": {"value": 6.530034e-18}, 
       "log.final.planet.Mass": {"value": 1.962337, "unit": u.Mearth}, 
       "log.final.planet.Radius": {"value": 2.717649e+07, "unit": u.m}, 
       "log.final.planet.RadGyra": {"value": 0.500000}, 
       "log.final.planet.BodyType": {"value": 0.000000}, 
       "log.final.planet.Density": {"value": 139.392053, "unit": u.kg / u.m ** 3}, 
       "log.final.planet.HZLimitDryRunaway": {"value": 1.357831e+11, "unit": u.m}, 
       "log.final.planet.HZLimRecVenus": {"value": 1.118929e+11, "unit": u.m}, 
       "log.final.planet.HZLimRunaway": {"value": 1.461108e+11, "unit": u.m}, 
       "log.final.planet.HZLimMoistGreenhouse": {"value": 1.480517e+11, "unit": u.m}, 
       "log.final.planet.HZLimMaxGreenhouse": {"value": 2.509538e+11, "unit": u.m}, 
       "log.final.planet.HZLimEarlyMars": {"value": 2.738109e+11, "unit": u.m}, 
       "log.final.planet.Instellation": {"value": 1.367567e+05, "unit": u.kg / u.sec ** 3}, 
       "log.final.planet.MeanMotion": {"value": 6.296062e-06, "unit": 1 / u.sec}, 
       "log.final.planet.OrbPeriod": {"value": 9.979548e+05, "unit": u.sec}, 
       "log.final.planet.SemiMajorAxis": {"value": 1.495979e+10, "unit": u.m}, 
       "log.final.planet.LXUVTot": {"value": -1.000000, "unit": u.kg / u.sec ** 3}, 
       "log.final.planet.SurfWaterMass": {"value": 0.000000, "unit": u.kg}, 
       "log.final.planet.EnvelopeMass": {"value": 0.022337, "unit": u.Mearth}, 
       "log.final.planet.OxygenMass": {"value": 0.000000, "unit": u.kg}, 
       "log.final.planet.RGLimit": {"value": 1.400774e+11, "unit": u.m}, 
       "log.final.planet.XO": {"value": 0.000000}, 
       "log.final.planet.EtaO": {"value": 0.000000}, 
       "log.final.planet.PlanetRadius": {"value": 4.260907, "unit": u.Rearth}, 
       "log.final.planet.OxygenMantleMass": {"value": 0.000000, "unit": u.kg}, 
       "log.final.planet.RadXUV": {"value": 4.260907, "unit": u.Rearth}, 
       "log.final.planet.RadSolid": {"value": 7.606867e+06, "unit": u.m}, 
       "log.final.planet.PresXUV": {"value": 5.000000}, 
       "log.final.planet.ScaleHeight": {"value": 273.737851, "unit": u.km}, 
       "log.final.planet.ThermTemp": {"value": 880.000000, "unit": u.K}, 
       "log.final.planet.AtmGasConst": {"value": 4157.000000}, 
       "log.final.planet.PresSurf": {"value": 2.451673, "unit": u.GPa}, 
       "log.final.planet.DEnvMassDt": {"value": -5.634095e+08, "unit": u.kg / u.sec}, 
       "log.final.planet.FXUV": {"value": 54.702677, "unit": u.W / u.m ** 2}, 
       "log.final.planet.AtmXAbsEffH2O": {"value": 0.150000}, 
       "log.final.planet.RocheRadius": {"value": 29.376060, "unit": u.Rearth}, 
       "log.final.planet.BondiRadius": {"value": 7.750709e+08, "unit": u.m}, 
       "log.final.planet.HEscapeRegime": {"value": 3.000000}, 
       "log.final.planet.RRCriticalFlux": {"value": 3.696953, "unit": u.W / u.m ** 2}, 
       "log.final.planet.KTide": {"value": 0.783955}, 
       "log.final.planet.RGDuration": {"value": 0.00000e+00, "unit": u.yr}, 
   } 
)
class TestMiniNeptuneEvapLC17(Benchmark): 
   pass 
