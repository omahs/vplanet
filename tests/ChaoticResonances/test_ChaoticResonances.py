import astropy.units as u
import pytest
from benchmark import Benchmark, benchmark


@benchmark(
    {
        "log.initial.system.Age": {"value": 0.0000000000000000, "unit": u.sec},
        "log.initial.system.Time": {"value": 0.0000000000000000, "unit": u.sec},
        "log.initial.system.TotAngMom": {
            "value": 8.3864645949891267e41,
            "unit": (u.kg * u.m ** 2) / u.sec,
        },
        "log.initial.system.TotEnergy": {
            "value": 2.9311287872491547e41,
            "unit": u.Joule,
        },
        "log.initial.system.PotEnergy": {
            "value": -1.0583876382908707e39,
            "unit": u.Joule,
        },
        "log.initial.system.KinEnergy": {
            "value": 2.9417132587727545e41,
            "unit": u.Joule,
        },
        "log.initial.system.DeltaTime": {"value": 0.0000000000000000, "unit": u.sec},
        "log.initial.star.Mass": {"value": 1.9884160000000000e30, "unit": u.kg},
        "log.initial.star.Radius": {"value": 1.4959787070000000e11, "unit": u.m},
        "log.initial.star.RadGyra": {"value": 0.5000000000000000},
        "log.initial.star.RotAngMom": {
            "value": 8.0902922047370218e46,
            "unit": (u.kg * u.m ** 2) / u.sec,
        },
        "log.initial.star.RotVel": {
            "value": 1.0879064157032310e06,
            "unit": u.m / u.sec,
        },
        "log.initial.star.BodyType": {"value": 0.0000000000000000},
        "log.initial.star.RotRate": {
            "value": 7.2722052166430393e-06,
            "unit": 1 / u.sec,
        },
        "log.initial.star.RotPer": {"value": 8.6400000000000000e05, "unit": u.sec},
        "log.initial.star.Density": {
            "value": 0.0001417889556243,
            "unit": u.kg / u.m ** 3,
        },
        "log.initial.star.HZLimitDryRunaway": {
            "value": 1.3578308258397624e11,
            "unit": u.m,
        },
        "log.initial.star.HZLimRecVenus": {"value": 1.1189291667421469e11, "unit": u.m},
        "log.initial.star.HZLimRunaway": {"value": 1.4611083895975479e11, "unit": u.m},
        "log.initial.star.HZLimMoistGreenhouse": {
            "value": 1.4805165010856509e11,
            "unit": u.m,
        },
        "log.initial.star.HZLimMaxGreenhouse": {
            "value": 2.5095375948691599e11,
            "unit": u.m,
        },
        "log.initial.star.HZLimEarlyMars": {
            "value": 2.7381088273450714e11,
            "unit": u.m,
        },
        "log.initial.star.Instellation": {
            "value": -1.0000000000000000,
            "unit": u.kg / u.sec ** 3,
        },
        "log.initial.star.Eccentricity": {"value": -1.0000000000000000},
        "log.initial.star.MeanMotion": {
            "value": -1.0000000000000000,
            "unit": 1 / u.sec,
        },
        "log.initial.star.OrbPeriod": {"value": -1.0000000000000000, "unit": u.sec},
        "log.initial.star.SemiMajorAxis": {"value": -1.0000000000000000, "unit": u.m},
        "log.initial.star.CriticalSemiMajorAxis": {
            "value": -1.0000000000000000,
            "unit": u.m,
        },
        "log.initial.star.COPP": {"value": 0.0000000000000000},
        "log.initial.star.OrbAngMom": {
            "value": 5.1310187442599682e37,
            "unit": (u.kg * u.m ** 2) / u.sec,
        },
        "log.initial.star.ArgP": {"value": 0.0000000000000000, "unit": u.rad},
        "log.initial.star.MeanAnomaly": {"value": 0.0000000000000000, "unit": u.rad},
        "log.initial.star.Inc": {"value": 0.0000000000000000, "unit": u.rad},
        "log.initial.star.LongA": {"value": 0.0000000000000000, "unit": u.rad},
        "log.initial.star.MeanLongitude": {"value": -1.0000000000000000, "unit": u.rad},
        "log.initial.star.LongP": {"value": 0.0000000000000000, "unit": u.rad},
        "log.initial.star.LXUVTot": {
            "value": 3.8460000000000003e23,
            "unit": u.kg / u.sec ** 3,
        },
        "log.initial.star.TotOrbEnergy": {
            "value": -3.0921071883090908e34,
            "unit": u.Joule,
        },
        "log.initial.star.OrbPotEnergy": {
            "value": -1.0000000000000000,
            "unit": u.Joule,
        },
        "log.initial.star.LostEnergy": {
            "value": 5.5626846462680035e-309,
            "unit": u.Joule,
        },
        "log.initial.star.LostAngMom": {
            "value": 5.5626846462680035e-309,
            "unit": (u.kg * u.m ** 2) / u.sec,
        },
        "log.initial.star.Luminosity": {"value": 3.8459999999999999e26, "unit": u.W},
        "log.initial.star.LXUVStellar": {"value": 3.8460000000000003e23, "unit": u.W},
        "log.initial.star.Temperature": {"value": 5778.0000000000000000, "unit": u.K},
        "log.initial.star.LXUVFrac": {"value": 0.0010000000000000},
        "log.initial.star.RossbyNumber": {"value": 0.7825964793302053},
        "log.initial.star.DRotPerDtStellar": {"value": 0.0125641125562794},
        "log.initial.star.PositionXSpiNBody": {"value": -1.4429418874286963e07},
        "log.initial.star.PositionYSpiNBody": {"value": -2.9345458658375326e06},
        "log.initial.star.PositionZSpiNBody": {"value": -4.5576042986373999e04},
        "log.initial.star.VelXSpiNBody": {"value": 0.2732150991008713},
        "log.initial.star.VelYSpiNBody": {"value": -1.7325692319189858},
        "log.initial.star.VelZSpiNBody": {"value": -0.0255936468723927},
        "log.initial.star.SpiNBodyInc": {"value": 0.0000000000000000, "unit": u.rad},
        "log.initial.star.SpiNBodyLongA": {"value": 0.0000000000000000, "unit": u.rad},
        "log.initial.earth.Mass": {"value": 5.9721859999999998e24, "unit": u.kg},
        "log.initial.earth.Radius": {"value": 6.3781000000000000e06, "unit": u.m},
        "log.initial.earth.RadGyra": {"value": 0.5000000000000000},
        "log.initial.earth.BodyType": {"value": 0.0000000000000000},
        "log.initial.earth.Density": {
            "value": 5495.0385490920862139,
            "unit": u.kg / u.m ** 3,
        },
        "log.initial.earth.HZLimitDryRunaway": {
            "value": 1.3731591322277353e11,
            "unit": u.m,
        },
        "log.initial.earth.HZLimRecVenus": {
            "value": 1.1189291667421469e11,
            "unit": u.m,
        },
        "log.initial.earth.HZLimRunaway": {"value": 1.4611083895975479e11, "unit": u.m},
        "log.initial.earth.HZLimMoistGreenhouse": {
            "value": 1.4805165010856509e11,
            "unit": u.m,
        },
        "log.initial.earth.HZLimMaxGreenhouse": {
            "value": 2.5095375948691599e11,
            "unit": u.m,
        },
        "log.initial.earth.HZLimEarlyMars": {
            "value": 2.7381088273450714e11,
            "unit": u.m,
        },
        "log.initial.earth.Instellation": {
            "value": 1383.0051502398405319,
            "unit": u.W / u.m ** 2,
        },
        "log.initial.earth.Eccentricity": {"value": 0.1490000000000000},
        "log.initial.earth.MeanMotion": {
            "value": 1.9909867499495633e-07,
            "unit": 1 / u.sec,
        },
        "log.initial.earth.OrbPeriod": {"value": 3.1558147272144098e07, "unit": u.sec},
        "log.initial.earth.SemiMajorAxis": {
            "value": 1.4959787070000000e11,
            "unit": u.m,
        },
        "log.initial.earth.COPP": {"value": 0.0000000000000000},
        "log.initial.earth.OrbAngMom": {
            "value": 2.6316636983764633e40,
            "unit": (u.kg * u.m ** 2) / u.sec,
        },
        "log.initial.earth.ArgP": {"value": 0.3167772592279167, "unit": u.rad},
        "log.initial.earth.MeanAnomaly": {"value": 3.8467056712855556, "unit": u.rad},
        "log.initial.earth.Inc": {"value": 0.7616616855485556, "unit": u.rad},
        "log.initial.earth.LongA": {"value": 4.5467572342404718, "unit": u.rad},
        "log.initial.earth.MeanLongitude": {"value": 3.8467056712855556, "unit": u.rad},
        "log.initial.earth.LongP": {"value": 0.0000000000000000, "unit": u.rad},
        "log.initial.earth.TotOrbEnergy": {
            "value": -3.0921071883090908e34,
            "unit": u.Joule,
        },
        "log.initial.earth.OrbPotEnergy": {
            "value": -1.4252414741147966e29,
            "unit": u.Joule,
        },
        "log.initial.earth.PositionXSpiNBody": {"value": -1.0927778675181111e11},
        "log.initial.earth.PositionYSpiNBody": {"value": -9.1630360917406158e10},
        "log.initial.earth.PositionZSpiNBody": {"value": -8.8363270583589447e10},
        "log.initial.earth.VelXSpiNBody": {"value": 1.0302727342823897e04},
        "log.initial.earth.VelYSpiNBody": {"value": -2.0544648815773355e04},
        "log.initial.earth.VelZSpiNBody": {"value": 1.2920067291495445e04},
        "log.initial.earth.SpiNBodyInc": {"value": 0.7616616855485556, "unit": u.rad},
        "log.initial.earth.SpiNBodyLongA": {"value": 4.5467572342404718, "unit": u.rad},
        "log.initial.outer.Mass": {"value": 1.3258252920000000e26, "unit": u.kg},
        "log.initial.outer.Radius": {"value": 2.4766162300000001e07, "unit": u.m},
        "log.initial.outer.RadGyra": {"value": 0.5000000000000000},
        "log.initial.outer.BodyType": {"value": 0.0000000000000000},
        "log.initial.outer.Density": {
            "value": 2083.6345315287080666,
            "unit": u.kg / u.m ** 3,
        },
        "log.initial.outer.HZLimitDryRunaway": {
            "value": 1.4124927831093353e11,
            "unit": u.m,
        },
        "log.initial.outer.HZLimRecVenus": {
            "value": 1.1189291667421469e11,
            "unit": u.m,
        },
        "log.initial.outer.HZLimRunaway": {"value": 1.4611083895975479e11, "unit": u.m},
        "log.initial.outer.HZLimMoistGreenhouse": {
            "value": 1.4805165010856509e11,
            "unit": u.m,
        },
        "log.initial.outer.HZLimMaxGreenhouse": {
            "value": 2.5095375948691599e11,
            "unit": u.m,
        },
        "log.initial.outer.HZLimEarlyMars": {
            "value": 2.7381088273450714e11,
            "unit": u.m,
        },
        "log.initial.outer.Instellation": {
            "value": 328.7916180138856248,
            "unit": u.kg / u.sec ** 3,
        },
        "log.initial.outer.Eccentricity": {"value": 0.2755000000000000},
        "log.initial.outer.MeanMotion": {
            "value": 6.6367563640053239e-08,
            "unit": 1 / u.sec,
        },
        "log.initial.outer.OrbPeriod": {"value": 9.4672532221563190e07, "unit": u.sec},
        "log.initial.outer.SemiMajorAxis": {
            "value": 3.1117853084306995e11,
            "unit": u.m,
        },
        "log.initial.outer.COPP": {"value": 0.0000000000000000},
        "log.initial.outer.OrbAngMom": {
            "value": 8.1896381029752160e41,
            "unit": (u.kg * u.m ** 2) / u.sec,
        },
        "log.initial.outer.ArgP": {"value": 0.9044296183576112, "unit": u.rad},
        "log.initial.outer.MeanAnomaly": {"value": 0.1172861257306667, "unit": u.rad},
        "log.initial.outer.Inc": {"value": 0.0221656814996944, "unit": u.rad},
        "log.initial.outer.LongA": {"value": 4.5467572342404718, "unit": u.rad},
        "log.initial.outer.MeanLongitude": {"value": 0.1172861257306667, "unit": u.rad},
        "log.initial.outer.LongP": {"value": 0.0000000000000000, "unit": u.rad},
        "log.initial.outer.TotOrbEnergy": {
            "value": -3.0921071883090908e34,
            "unit": u.Joule,
        },
        "log.initial.outer.OrbPotEnergy": {
            "value": 0.0000000000000000,
            "unit": u.Joule,
        },
        "log.initial.outer.PositionXSpiNBody": {"value": 2.2132866830605267e11},
        "log.initial.outer.PositionYSpiNBody": {"value": 4.8138556033905289e10},
        "log.initial.outer.PositionZSpiNBody": {"value": 4.6638574804342966e09},
        "log.initial.outer.VelXSpiNBody": {"value": -4561.6498805816136155},
        "log.initial.outer.VelYSpiNBody": {"value": 2.6909766071108414e04},
        "log.initial.outer.VelZSpiNBody": {"value": -198.1424567507141887},
        "log.initial.outer.SpiNBodyInc": {"value": 0.0221656814996944, "unit": u.rad},
        "log.initial.outer.SpiNBodyLongA": {"value": 4.5467572342404718, "unit": u.rad},
        "log.final.system.Age": {
            "value": 3.1557600000000000e08,
            "unit": u.sec,
            "rtol": 1e-4,
        },
        "log.final.system.Time": {
            "value": 3.1557600000000000e08,
            "unit": u.sec,
            "rtol": 1e-4,
        },
        "log.final.system.TotAngMom": {
            "value": 8.3864645949891592e41,
            "unit": (u.kg * u.m ** 2) / u.sec,
            "rtol": 1e-4,
        },
        "log.final.system.TotEnergy": {
            "value": 2.9311287872491675e41,
            "unit": u.Joule,
            "rtol": 1e-4,
        },
        "log.final.system.PotEnergy": {
            "value": -1.0583876382908707e39,
            "unit": u.Joule,
            "rtol": 1e-4,
        },
        "log.final.system.KinEnergy": {
            "value": 6.6863736376522519e40,
            "unit": u.Joule,
            "rtol": 1e-4,
        },
        "log.final.system.DeltaTime": {
            "value": 458.4461618920332171,
            "unit": u.sec,
            "rtol": 1e-4,
        },
        "log.final.star.Mass": {
            "value": 1.9884160000000000e30,
            "unit": u.kg,
            "rtol": 1e-4,
        },
        "log.final.star.Radius": {
            "value": 1.4959787070000000e11,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.star.RadGyra": {"value": 0.5000000000000000, "rtol": 1e-4},
        "log.final.star.RotAngMom": {
            "value": 3.8570863306754262e46,
            "unit": (u.kg * u.m ** 2) / u.sec,
            "rtol": 1e-4,
        },
        "log.final.star.RotVel": {
            "value": 5.1866469824243232e05,
            "unit": u.m / u.sec,
            "rtol": 1e-4,
        },
        "log.final.star.BodyType": {"value": 0.0000000000000000, "rtol": 1e-4},
        "log.final.star.RotRate": {
            "value": 3.4670593626466122e-06,
            "unit": 1 / u.sec,
            "rtol": 1e-4,
        },
        "log.final.star.RotPer": {
            "value": 1.8122520124325929e06,
            "unit": u.sec,
            "rtol": 1e-4,
        },
        "log.final.star.Density": {
            "value": 0.0001417889556243,
            "unit": u.kg / u.m ** 3,
            "rtol": 1e-4,
        },
        "log.final.star.HZLimitDryRunaway": {
            "value": 1.3578308258397624e11,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.star.HZLimRecVenus": {
            "value": 1.1189291667421469e11,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.star.HZLimRunaway": {
            "value": 1.4611083895975479e11,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.star.HZLimMoistGreenhouse": {
            "value": 1.4805165010856509e11,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.star.HZLimMaxGreenhouse": {
            "value": 2.5095375948691599e11,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.star.HZLimEarlyMars": {
            "value": 2.7381088273450714e11,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.star.Instellation": {
            "value": -1.0000000000000000,
            "unit": u.kg / u.sec ** 3,
            "rtol": 1e-4,
        },
        "log.final.star.Eccentricity": {"value": -1.0000000000000000, "rtol": 1e-4},
        "log.final.star.MeanMotion": {
            "value": -1.0000000000000000,
            "unit": 1 / u.sec,
            "rtol": 1e-4,
        },
        "log.final.star.OrbPeriod": {
            "value": -1.0000000000000000,
            "unit": u.sec,
            "rtol": 1e-4,
        },
        "log.final.star.SemiMajorAxis": {
            "value": -1.0000000000000000,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.star.CriticalSemiMajorAxis": {
            "value": -1.0000000000000000,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.star.COPP": {"value": 0.0000000000000000, "rtol": 1e-4},
        "log.final.star.OrbAngMom": {
            "value": 5.6533243870734744e37,
            "unit": (u.kg * u.m ** 2) / u.sec,
            "rtol": 1e-4,
        },
        "log.final.star.ArgP": {
            "value": 0.0000000000000000,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.star.MeanAnomaly": {
            "value": 0.0000000000000000,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.star.Inc": {
            "value": 0.0000000000000000,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.star.LongA": {
            "value": 0.0000000000000000,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.star.MeanLongitude": {
            "value": -1.0000000000000000,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.star.LongP": {
            "value": 0.0000000000000000,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.star.LXUVTot": {
            "value": 3.8460000000000003e23,
            "unit": u.kg / u.sec ** 3,
            "rtol": 1e-4,
        },
        "log.final.star.TotOrbEnergy": {
            "value": -3.0921071883090410e34,
            "unit": u.Joule,
            "rtol": 1e-4,
        },
        "log.final.star.OrbPotEnergy": {
            "value": -1.0000000000000000,
            "unit": u.Joule,
            "rtol": 1e-4,
        },
        "log.final.star.LostEnergy": {
            "value": 2.2730758950075419e41,
            "unit": u.Joule,
            "rtol": 1e-4,
        },
        "log.final.star.LostAngMom": {
            "value": 4.2332058740615758e46,
            "unit": (u.kg * u.m ** 2) / u.sec,
            "rtol": 1e-4,
        },
        "log.final.star.Luminosity": {
            "value": 3.8459999999999999e26,
            "unit": u.W,
            "rtol": 1e-4,
        },
        "log.final.star.LXUVStellar": {
            "value": 3.8460000000000003e23,
            "unit": u.W,
            "rtol": 1e-4,
        },
        "log.final.star.Temperature": {
            "value": 5778.0000000000000000,
            "unit": u.K,
            "rtol": 1e-4,
        },
        "log.final.star.LXUVFrac": {"value": 0.0010000000000000, "rtol": 1e-4},
        "log.final.star.RossbyNumber": {"value": 1.6415069960518827, "rtol": 1e-4},
        "log.final.star.DRotPerDtStellar": {"value": 0.0013614988340492, "rtol": 1e-4},
        "log.final.star.PositionXSpiNBody": {
            "value": 2.1308698850179501e07,
            "rtol": 1e-4,
        },
        "log.final.star.PositionYSpiNBody": {
            "value": -1.3224372171482876e07,
            "rtol": 1e-4,
        },
        "log.final.star.PositionZSpiNBody": {
            "value": 7.7284217839499633e05,
            "rtol": 1e-4,
        },
        "log.final.star.VelXSpiNBody": {"value": 0.7437655337158928, "rtol": 1e-4},
        "log.final.star.VelYSpiNBody": {"value": 0.8715622791637967, "rtol": 1e-4},
        "log.final.star.VelZSpiNBody": {"value": -0.0249334971783929, "rtol": 1e-4},
        "log.final.star.SpiNBodyInc": {
            "value": 0.0000000000000000,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.star.SpiNBodyLongA": {
            "value": 0.0000000000000000,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.earth.Mass": {
            "value": 5.9721859999999998e24,
            "unit": u.kg,
            "rtol": 1e-4,
        },
        "log.final.earth.Radius": {
            "value": 6.3781000000000000e06,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.earth.RadGyra": {"value": 0.5000000000000000, "rtol": 1e-4},
        "log.final.earth.BodyType": {"value": 0.0000000000000000, "rtol": 1e-4},
        "log.final.earth.Density": {
            "value": 5495.0385490920862139,
            "unit": u.kg / u.m ** 3,
            "rtol": 1e-4,
        },
        "log.final.earth.HZLimitDryRunaway": {
            "value": 1.3731832271378857e11,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.earth.HZLimRecVenus": {
            "value": 1.1189291667421469e11,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.earth.HZLimRunaway": {
            "value": 1.4611083895975479e11,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.earth.HZLimMoistGreenhouse": {
            "value": 1.4805165010856509e11,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.earth.HZLimMaxGreenhouse": {
            "value": 2.5095375948691599e11,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.earth.HZLimEarlyMars": {
            "value": 2.7381088273450714e11,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.earth.Instellation": {
            "value": 1383.2882055348156882,
            "unit": u.W / u.m ** 2,
            "rtol": 1e-4,
        },
        "log.final.earth.Eccentricity": {"value": 0.1491151035228643, "rtol": 1e-4},
        "log.final.earth.MeanMotion": {
            "value": 1.9912661532603589e-07,
            "unit": 1 / u.sec,
            "rtol": 1e-4,
        },
        "log.final.earth.OrbPeriod": {
            "value": 3.1553719209719613e07,
            "unit": u.sec,
            "rtol": 1e-4,
        },
        "log.final.earth.SemiMajorAxis": {
            "value": 1.4958387654931546e11,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.earth.COPP": {"value": 0.0001228834213755, "rtol": 1e-4},
        "log.final.earth.OrbAngMom": {
            "value": 2.6310398584174738e40,
            "unit": (u.kg * u.m ** 2) / u.sec,
            "rtol": 1e-4,
        },
        "log.final.earth.ArgP": {
            "value": 1.7388411561743455,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.earth.MeanAnomaly": {
            "value": 3.8474870280350597,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.earth.Inc": {
            "value": 0.7616663331648604,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.earth.LongA": {
            "value": 4.5464158170091213,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.earth.MeanLongitude": {
            "value": 3.8495586940389401,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.earth.LongP": {
            "value": 0.0020716660038804,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.earth.TotOrbEnergy": {
            "value": -3.0921071883090410e34,
            "unit": u.Joule,
            "rtol": 1e-4,
        },
        "log.final.earth.OrbPotEnergy": {
            "value": -1.4358907359336649e29,
            "unit": u.Joule,
            "rtol": 1e-4,
        },
        "log.final.earth.PositionXSpiNBody": {
            "value": -1.0910217698713353e11,
            "rtol": 1e-4,
        },
        "log.final.earth.PositionYSpiNBody": {
            "value": -9.2003427654772461e10,
            "rtol": 1e-4,
        },
        "log.final.earth.PositionZSpiNBody": {
            "value": -8.8139271268419617e10,
            "rtol": 1e-4,
        },
        "log.final.earth.VelXSpiNBody": {"value": 1.0346177290713909e04, "rtol": 1e-4},
        "log.final.earth.VelYSpiNBody": {"value": -2.0495887004595304e04, "rtol": 1e-4},
        "log.final.earth.VelZSpiNBody": {"value": 1.2959382255760662e04, "rtol": 1e-4},
        "log.final.earth.SpiNBodyInc": {
            "value": 0.7616663331648604,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.earth.SpiNBodyLongA": {
            "value": 4.5464158170091213,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.outer.Mass": {
            "value": 1.3258252920000000e26,
            "unit": u.kg,
            "rtol": 1e-4,
        },
        "log.final.outer.Radius": {
            "value": 2.4766162300000001e07,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.outer.RadGyra": {"value": 0.5000000000000000, "rtol": 1e-4},
        "log.final.outer.BodyType": {"value": 0.0000000000000000, "rtol": 1e-4},
        "log.final.outer.Density": {
            "value": 2083.6345315287080666,
            "unit": u.kg / u.m ** 3,
            "rtol": 1e-4,
        },
        "log.final.outer.HZLimitDryRunaway": {
            "value": 1.4124949215240683e11,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.outer.HZLimRecVenus": {
            "value": 1.1189291667421469e11,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.outer.HZLimRunaway": {
            "value": 1.4611083895975479e11,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.outer.HZLimMoistGreenhouse": {
            "value": 1.4805165010856509e11,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.outer.HZLimMaxGreenhouse": {
            "value": 2.5095375948691599e11,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.outer.HZLimEarlyMars": {
            "value": 2.7381088273450714e11,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.outer.Instellation": {
            "value": 328.7796826161163040,
            "unit": u.kg / u.sec ** 3,
            "rtol": 1e-4,
        },
        "log.final.outer.Eccentricity": {"value": 0.2755050780615579, "rtol": 1e-4},
        "log.final.outer.MeanMotion": {
            "value": 6.6365681380548247e-08,
            "unit": 1 / u.sec,
            "rtol": 1e-4,
        },
        "log.final.outer.OrbPeriod": {
            "value": 9.4675217318286806e07,
            "unit": u.sec,
            "rtol": 1e-4,
        },
        "log.final.outer.SemiMajorAxis": {
            "value": 3.1118441456657074e11,
            "unit": u.m,
            "rtol": 1e-4,
        },
        "log.final.outer.COPP": {"value": 4.9414297148998368e-06, "rtol": 1e-4},
        "log.final.outer.OrbAngMom": {
            "value": 8.1896514223697359e41,
            "unit": (u.kg * u.m ** 2) / u.sec,
            "rtol": 1e-4,
        },
        "log.final.outer.ArgP": {
            "value": 1.7362790073768688,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.outer.MeanAnomaly": {
            "value": 2.2114076505371290,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.outer.Inc": {
            "value": 0.0221682336065829,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.outer.LongA": {
            "value": 4.5469441076918793,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.outer.MeanLongitude": {
            "value": 2.2114454584262906,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.outer.LongP": {
            "value": 3.7807889161634023e-05,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.outer.TotOrbEnergy": {
            "value": -3.0921071883090410e34,
            "unit": u.Joule,
            "rtol": 1e-4,
        },
        "log.final.outer.OrbPotEnergy": {
            "value": 0.0000000000000000,
            "unit": u.Joule,
            "rtol": 1e-4,
        },
        "log.final.outer.PositionXSpiNBody": {
            "value": -3.1466422831611719e11,
            "rtol": 1e-4,
        },
        "log.final.outer.PositionYSpiNBody": {
            "value": 2.0247776958475812e11,
            "rtol": 1e-4,
        },
        "log.final.outer.PositionZSpiNBody": {
            "value": -7.6205186095987511e09,
            "rtol": 1e-4,
        },
        "log.final.outer.VelXSpiNBody": {"value": -1.1620721010188581e04, "rtol": 1e-4},
        "log.final.outer.VelYSpiNBody": {"value": -1.2148079699322327e04, "rtol": 1e-4},
        "log.final.outer.VelZSpiNBody": {"value": -209.8140435160255208, "rtol": 1e-4},
        "log.final.outer.SpiNBodyInc": {
            "value": 0.0221682336065829,
            "unit": u.rad,
            "rtol": 1e-4,
        },
        "log.final.outer.SpiNBodyLongA": {
            "value": 4.5469441076918793,
            "unit": u.rad,
            "rtol": 1e-4,
        },
    }
)
class TestChaoticResonances(Benchmark):
    pass
