#ifndef BfCompetition_H
#define BfCompetition_H

#include <list>
#include <QString>

class BfCompetition {
  public:
  enum Competition {
    ALL=-1,
    UNKOWN=-2,
    AFC_Cup=309972,
    ARE_UAE_Emirates_Cup_Group_Stage=4039797,
    ARE_UAE_Premier_League=258537,
    ARG_Argentinian_Primera_B_Metropolitana=3765124,
    ARG_Argentinian_Primera_B_Nacional=803237,
    ARG_Argentinian_Primera_C_Metropolitana=7511144,
    ARG_Argentinian_Primera_Division=67387,
    ARG_Copa_Argentina=1227903,
    ARG_Torneo_Federal_A=7617364,
    ARM_Armenian_First_League=3061353,
    ARM_Armenian_Premier_League=2888729,
    AUT_Austrian_Bundesliga=7,
    AUT_Austrian_OFB_Ladies_Cup=7593578,
    AUT_Austrian_Regionalliga=7317506,
    AUT_Erste_Liga=9,
    AUT_Samsung_Cup=167716,
    AZE_Azerbaijan_Premier=895129,
    AZE_I_Divizion=4517491,
    BEL_Belgian_Jupiler_League=89979,
    BEL_Belgian_Second_Division=164952,
    BEL_Beloften_Pro_League=3037492,
    BEL_Super_League_women=8189587,
    BGD_Bangladeshi_Premier_League=5388369,
    BGR_Bulgarian_B_PFG=5618298,
    BGR_Bulgarian_Cup=309948,
    BGR_Bulgarian_Premier=15,
    BGR_Bulgarian_Super_Cup=338432,
    BGR_Bulgarian_U19_League=8211415,
    BHR_Bahrain_FA_Cup=1478090,
    BIH_Bosnian_Premier_League=3127357,
    BLR_Belarus_League_W=1079277,
    BLR_Belarusian_1st_Division=3126267,
    BLR_Belarusian_Premier_League=888275,
    BOL_Bolivian_Liga_Nacional_A=3729355,
    BRA_Brazil_Carioca_U20=7425648,
    BRA_Brazilian_Cup=89219,
    BRA_Brazilian_Division_2=321319,
    BRA_Brazilian_Paranaense_U19=7717120,
    BRA_Brazilian_Serie_C=3172302,
    BRA_Brazilian_Serie_D=7980087,
    BRA_Brazilian_Taca_FPF=7883210,
    BRA_Campeonato=13,
    BRA_Campeonato_Valmir_Louruz=8011625,
    BRA_Copa_Paulista=3583988,
    BRA_Copa_Rio=5982310,
    BRA_Copa_do_Brasil_U20=3744990,
    BRA_Paulista_U20=3127716,
    BRA_Serie_C=3172302,
    BRA_U20_Championship=804633,
    BRB_Barbados_Premier_League=4644792,
    CAF_Champions_League=987643,
    CAN_Canadian_Championship=908099,
    CAN_Canadian_PCSL=5389244,
    CAN_Ontario_League_1=5339687,
    CHE_Swiss_Challenge_League=135,
    CHE_Swiss_Super_League=133,
    CHE_Swisscom_Cup=29051,
    CHL_Chilean_Cup=961354,
    CHL_Chilean_Primera=744098,
    CHL_Chilean_Primera_B=857992,
    CHL_Chilean_Segunda_Division=3085749,
    CHN_Chinese_Super_League=879931,
    COL_Colombian_Primera_A=844197,
    COL_Colombian_Primera_B=856134,
    COL_Copa_Colombia=854148,
    CRI_Costa_Rican_Primera_Division=2079376,
    CZE_1_Liga_Women=3765192,
    CZE_Czech_2_Liga=862638,
    CZE_Czech_3_Liga=892425,
    CZE_Czech_Republic_Cup=97807,
    CZE_Czech_U19_League=1987477,
    CZE_Czech_U21_League=4848838,
    CZE_Synot_Liga=21,
    DEU_3_Liga=158146,
    DEU_Bavarian_Cup=7152675,
    DEU_Bundesliga_1=59,
    DEU_Bundesliga_2=61,
    DEU_Bundesliga_W=6294253,
    DEU_German_Junioren_Bundesliga=852459,
    DEU_Regionalliga_Bayern=853948,
    DEU_Regionalliga_Nord=63,
    DEU_Regionalliga_Nordost=318343,
    DEU_Regionalliga_Sudwest=65,
    DEU_Regionalliga_West=840808,
    DEU_Westfalenpokal=1242586,
    DNK_Danish_Cup=30921,
    DNK_Danish_Division_1=25,
    DNK_Danish_Division_2=7998231,
    DNK_Danish_Reserve_League=858294,
    DNK_Danish_Superliga=23,
    DNK_Danish_U19_League=940730,
    DNK_Danish_U21_League=886334,
    DNK_Denmark_Series=8244827,
    DNK_Division_2_East=29,
    DNK_Division_2_West=27,
    DNK_Elitedivisionen_W=3221347,
    DZA_Algerian_Ligue_1=4431442,
    DZA_Algerian_U21_Ligue_1=3792498,
    DZA_Algerian_U21_Ligue_2=4556663,
    ECU_Ecuadorian_Primera_A=803690,
    ECU_Ecuadorian_Serie_B=3057583,
    EGY_Egyptian_Cup=802004,
    EGY_Egyptian_Premier=801976,
    ESP_Copa_Catalunya=1032778,
    ESP_Primera_Division=117,
    ESP_Primera_Division_W=6362364,
    ESP_Segunda_B1=121,
    ESP_Segunda_B2=123,
    ESP_Segunda_B3=125,
    ESP_Segunda_B4=127,
    ESP_Segunda_Division=119,
    ESP_Segunda_Division_women=4608262,
    ESP_Spanish_Copa_Federacion=834025,
    ESP_Spanish_Cup=12801,
    ESP_Spanish_Supercup=584,
    ESP_Tercera_Division=821269,
    EST_Esiliiga_B=2901699,
    EST_Estonian_Cup=886734,
    EST_Estonian_Esiliiga=873203,
    EST_Estonian_II_Liga=5699678,
    EST_Estonian_Meistriliiga=862545,
    EST_Estonian_Meistriliiga_Women=3221481,
    EST_Estonian_Small_Cup=7594575,
    FAI_Cup=7485811,
    FIN_Finnish_Cup=20601,
    FIN_Finnish_Kolmonen=5281887,
    FIN_Finnish_Naistenliiga_W=982877,
    FIN_Finnish_U19_League=1684210,
    FIN_Kakkonen_East=53,
    FIN_Kakkonen_North=51,
    FIN_Kakkonen_South=49,
    FIN_Kakkonen_West=1551845,
    FIN_Veikkausliiga=45,
    FIN_Ykkonen=47,
    FRA_Coupe_de_la_Ligue=22358,
    FRA_French_League_W=6023868,
    FRA_Ligue_1_Orange=55,
    FRA_Ligue_2_Orange=57,
    FRA_Ligue_National=1081960,
    FRA_Toulon_Tournament=91729,
    GBR_AFC_Cup=309972,
    GBR_Barclays_Premier_League=31,
    GBR_Capital_One_Cup=2134,
    GBR_English_FA_Cup=30558,
    GBR_Friendlies_W=4684340,
    GBR_Isthmian_Premier=820582,
    GBR_Johnstones_Paint_Trophy=24789,
    GBR_Lancashire_Senior_Cup=1279245,
    GBR_League_One=35,
    GBR_League_Two=37,
    GBR_NIFL_Premiership=20351,
    GBR_NIFL_Reserve_League=4540650,
    GBR_National_League=39,
    GBR_National_League_North=41,
    GBR_National_League_South=43,
    GBR_Northern_Premier=820753,
    GBR_Professional_Development_League=2129602,
    GBR_SPFL_Development_League=5808320,
    GBR_SPFL_Development_League_2=6011072,
    GBR_Scottish_Challenge_Cup=334679,
    GBR_Scottish_Championship=107,
    GBR_Scottish_Cup=409743,
    GBR_Scottish_League_One=109,
    GBR_Scottish_League_Two=111,
    GBR_Scottish_Premiership=105,
    GBR_Scottish_SWFL_Women=7672495,
    GBR_Scottish_Womens_Premier_League=7552802,
    GBR_Specials=2608550,
    GBR_The_Championship=7129730,
    GBR_Welsh_League_Cup=695030,
    GBR_Welsh_Premier_League=252549,
    GBR_Womens_Super_League=887470,
    GEO_Georgian_Division_1=4040072,
    GEO_Pirveli_Liga=2356065,
    GIB_Gibraltar_Premier_Division=6182297,
    GRC_Greek_Division_2=69,
    GRC_Greek_Football_League=833616,
    GRC_Greek_Super_League=67,
    GRC_Greek_U20_Super_League=824417,
    GTM_Guatemalan_Liga_Nacional=6566654,
    GTM_Guatemalan_Primera_Division_de_Ascenso=6812603,
    HKG_Hong_Kong_Division_1=833990,
    HND_Liga_Nacional=4517524,
    HRV_Croatian_3_HNL=7596190,
    HRV_Croatian_Division_1=17,
    HRV_Croatian_Division_2=3992967,
    HRV_Croatian_U19_League=3765131,
    HUN_Hungarian_Cup=94603,
    HUN_Hungarian_NB_I=1842928,
    HUN_Hungarian_NB_II=4556576,
    HUN_Hungarian_NB_I_W=8211299,
    HUN_Hungarian_U19_Division_1=311575,
    IDN_Indonesian_Cup=8085064,
    IDN_Presidents_Cup=845150,
    IND_Calcutta_Premier_Division=2462835,
    IND_Delhi_Senior_Division=7995514,
    IND_Goa_Professional_League=3781558,
    IND_Indian_Super_League=6251219,
    IND_Mumbai_Elite_Division_League=5007039,
    IRL_Airtricity_First_Division=79,
    IRL_Airtricity_Premier_Division=77,
    IRL_EA_Sports_Cup=24865,
    IRL_FAI_Cup=7485811,
    ISL_Icelandic_1st_Division_W=984404,
    ISL_Icelandic_Cup=154811,
    ISL_Icelandic_Cup_W=827084,
    ISL_Icelandic_First_Division=905441,
    ISL_Icelandic_Fourth_Division=5618314,
    ISL_Icelandic_Premier_League_W=911286,
    ISL_Icelandic_Second_Division=943450,
    ISL_Icelandic_Third_Division=3126286,
    ISL_Icelandic_U19_League=907589,
    ISL_Icelandic_U19_League_Women=3244094,
    ISL_Urvalsdeild=887158,
    ISR_Israeli_Liga_Alef=5618479,
    ISR_Israeli_Liga_Leumit=804044,
    ISR_Israeli_Liga_Leumit_Cup=1035449,
    ISR_Israeli_Premier=822165,
    ISR_Israeli_Premier_League_Cup=1161205,
    ISR_Israeli_Super_Cup=8083549,
    ISR_Israeli_U19_Elite_Division=2465205,
    ITA_Campeonato_Primavera=841133,
    ITA_Coppa_Italia=1874,
    ITA_Coppa_Italia_Lega_Pro=849268,
    ITA_Lega_Pro=5984496,
    ITA_Serie_A=81,
    ITA_Serie_B=83,
    International_AFC_Champions_League=39218,
    International_AFC_Cup=309972,
    International_CAF_African_Cup_of_Nations=4254855,
    International_CAF_Champions_League=987643,
    International_CAF_Confederations_Cup=2001733,
    International_CONCACAF_Champions_League=194961,
    International_Copa_Sudamericana=4655,
    International_Euro_2016=4527196,
    International_FIFA_World_Cup_2018=5614746,
    International_Friendly=219,
    International_International_Friendly=1985077,
    International_International_Friendly_W=88832,
    International_U19_Internationals=13051,
    International_U20_International=402969,
    International_U21_Euro_Championships_Qualifiers=7597618,
    International_U21_International=6301,
    International_UEFA_Champions_League=228,
    International_UEFA_Europa_League=2005,
    International_UEFA_Youth_League=3784863,
    JAM_Jamaican_Premier_League=3796898,
    JOR_Jordan_Cup=900926,
    JOR_Jordan_League=843222,
    JPN_Emperors_Cup=236552,
    JPN_J2_League=1062024,
    JPN_J3_League=4802285,
    JPN_J_League=89,
    JPN_Japan_Football_League=3785366,
    JPN_Japanese_League_W=7143446,
    JPN_Nabisco_Cup=32518,
    KAZ_Kazakhstani_1_Division=3297851,
    KAZ_Kazakhstani_Premier_League=3127737,
    KEN_Kenyan_Premier_League=7616742,
    KOR_K_League=867459,
    LTU_Lithuanian_1_Lyga=1587980,
    LTU_Lithuanian_A_Lyga=879221,
    LTU_Lithuanian_Cup=1147862,
    LUX_Luxembourg_National_Division=4515700,
    LVA_Latvian_1_Liga=1661891,
    LVA_Latvian_Reserve_League=7183687,
    LVA_Latvian_Second_League=3242305,
    LVA_Virsliga=887178,
    MAR_Moroccan_Cup=4095837,
    MAR_Moroccan_Division_1=2609677,
    MEX_Copa_Mexico=1979279,
    MEX_Mexican_Liga_de_Ascenso=827754,
    MEX_Mexican_Primera_Division=5627174,
    MEX_Mexican_U20_League=827078,
    MKD_Macedonian_Football_League=1517121,
    MLS=141,
    MLT_Maltese_First_Division=2923434,
    MLT_Maltese_Premier_League=1327393,
    MMR_Myanmar_National_League=7836682,
    MYS_Malaysia_Cup=1105022,
    MYS_Malaysian_Super_League=840886,
    NIC_Nicaraguan_Primera_Division=6480193,
    NIFL_Premiership=20351,
    NLD_Dutch_Jong_Eredivisie=836645,
    NLD_Dutch_Jupiler_League=11,
    NLD_Eredivisie=71,
    NLD_Eredivisie_W=8139939,
    NLD_Netherlands_Reserve_League=8068520,
    NOR_Norwegian_1_Division=95,
    NOR_Norwegian_2_Division=891106,
    NOR_Norwegian_3_Division=920858,
    NOR_Norwegian_Cup=4051,
    NOR_Norwegian_League_W=7126020,
    NOR_Tippeligaen=93,
    PAN_Panama_Primera_Division=3972877,
    PER_Peru_Primera_Division=848082,
    PHL_Philippines_UFL_Cup=7319790,
    PHL_UFL_Division=6871833,
    POL_Ekstraklasa=97,
    POL_Ekstraliga_W=7138694,
    POL_Polish_1_Liga=403085,
    POL_Polish_2_Liga=876442,
    POL_Polish_Cup=32246,
    POL_Polish_U19_Central_Junior_League=5449376,
    PRT_Campeonato_Nacional_Seniores=4517616,
    PRT_Portugese_Super_Cup_Women=8166570,
    PRT_Portuguese_U19_Championship=863810,
    PRT_Primeira_Liga=99,
    PRT_Segunda_Liga=9513,
    PRT_Taca_da_Liga=19640,
    PRT_Taca_de_Portugal=61351,
    PRY_Paraguayan_Primera=839575,
    QAT_Qatari_Stars_League=842258,
    ROU_Liga_1=4905,
    ROU_Romanian_Cup=218756,
    ROU_Romanian_Liga_II=862579,
    ROU_Romanian_Liga_III=3006957,
    RUS_Premier_Division=101,
    RUS_Russian_Cup=33051,
    RUS_Russian_Division_1=880458,
    RUS_Russian_Division_2=891179,
    RUS_Russian_Regional_Leagues=7425130,
    RUS_Russian_Youth_League=868392,
    SAU_Saudi_Crown_Prince_Cup=840912,
    SAU_Saudi_Premier=853446,
    SGP_Singapore_Cup=944127,
    SGP_Singapore_Prime_League=868823,
    SGP_Singapore_S_League=848322,
    SLV_El_Salvadoran_Primera_Division=4802204,
    SRB_Serbian_Super_Liga=103,
    SVK_1_Liga_East=5714159,
    SVK_1_Liga_West=5713494,
    SVK_Slovakian_1_Liga=2938065,
    SVK_Slovakian_Cup=97855,
    SVK_Slovakian_Super_Liga=113,
    SVK_Slovakian_U19_League=872270,
    SVN_2_SNL=8141281,
    SVN_Slovenian_Prva_Liga=115,
    SWE_Allsvenskan=129,
    SWE_Superettan=131,
    SWE_Swedish_Cup=18099,
    SWE_Swedish_Div_1_Norra=500102,
    SWE_Swedish_Div_1_Sodra=500180,
    SWE_Swedish_Division_1_W=7261893,
    SWE_Swedish_Division_2=920223,
    THA_Thailand_Division_1=4608858,
    THA_Thailand_Division_2=4608865,
    THA_Thailand_FA_Cup=3297875,
    THA_Thailand_League_Cup=5448752,
    THA_Thailand_Premier_League=3332575,
    TUN_Tunisian_Cup=6390405,
    TUN_Tunisian_Ligue_Professionelle_1=6103298,
    TUR_Turkish_Division_1=175680,
    TUR_Turkish_Super_League=194215,
    UEFA_Champions_League=228,
    UEFA_Europa_League=2005,
    UKR_Ukrainian_Cup=300965,
    UKR_Ukrainian_Druha_Liga=1658999,
    UKR_Ukrainian_League_W=3089001,
    UKR_Ukrainian_Persha_Liga=872215,
    UKR_Ukrainian_U19_League=1888360,
    UKR_Ukrainian_U21_League=7946082,
    UKR_Vischya_Liga=139,
    URY_Uruguayan_Primera=843454,
    URY_Uruguayan_Segunda_Division=6104087,
    USA_MLS=141,
    USA_NPSL=5618531,
    USA_North_American_Soccer_League=156320,
    USA_USL_Pro=3004992,
    USA_US_Open_Cup=155369,
    USA_US_PDL=7465669,
    USL_Pro=3004992,
    UZB_Uzbekistan_1_Division=7197874,
    UZB_Uzbekistan_Cup=4851739,
    UZB_Uzbekistan_Professional_League=908196,
    UZB_Uzbekistan_Youth_League_U23=4732508,
    VEN_Copa_Venezuela=7893771,
    VEN_Liga_de_Ascenso=7897688,
    VEN_Venezuelan_Primera=1065530,
    VNM_National_Cup=4608119,
    VNM_VLeague_1=4555345,
    VNM_VLeague_2=5326228,
    ZAF_8_Cup=5790028,
    ZAF_Premier_Soccer_League=2631619,
    ZAF_South_African_First_Division=3785359,
    ZAF_South_African_League_Cup=6197407,
    ZAF_South_African_Varsity_Football_Challenge=7942109,
  };

  static QString toStr(Competition cp) {
    if (cp == ALL) {
      return QString("ALL");
    } else if (cp == AFC_Cup) {
      return QString("AFC_Cup");
    } else if (cp == AFC_Cup) {
      return QString("AFC_Cup");
    } else if (cp == ARE_UAE_Emirates_Cup_Group_Stage) {
      return QString("ARE_UAE_Emirates_Cup_Group_Stage");
    } else if (cp == ARE_UAE_Premier_League) {
      return QString("ARE_UAE_Premier_League");
    } else if (cp == ARG_Argentinian_Primera_B_Metropolitana) {
      return QString("ARG_Argentinian_Primera_B_Metropolitana");
    } else if (cp == ARG_Argentinian_Primera_B_Nacional) {
      return QString("ARG_Argentinian_Primera_B_Nacional");
    } else if (cp == ARG_Argentinian_Primera_C_Metropolitana) {
      return QString("ARG_Argentinian_Primera_C_Metropolitana");
    } else if (cp == ARG_Argentinian_Primera_Division) {
      return QString("ARG_Argentinian_Primera_Division");
    } else if (cp == ARG_Copa_Argentina) {
      return QString("ARG_Copa_Argentina");
    } else if (cp == ARG_Torneo_Federal_A) {
      return QString("ARG_Torneo_Federal_A");
    } else if (cp == ARM_Armenian_First_League) {
      return QString("ARM_Armenian_First_League");
    } else if (cp == ARM_Armenian_Premier_League) {
      return QString("ARM_Armenian_Premier_League");
    } else if (cp == AUT_Austrian_Bundesliga) {
      return QString("AUT_Austrian_Bundesliga");
    } else if (cp == AUT_Austrian_OFB_Ladies_Cup) {
      return QString("AUT_Austrian_OFB_Ladies_Cup");
    } else if (cp == AUT_Austrian_Regionalliga) {
      return QString("AUT_Austrian_Regionalliga");
    } else if (cp == AUT_Erste_Liga) {
      return QString("AUT_Erste_Liga");
    } else if (cp == AUT_Samsung_Cup) {
      return QString("AUT_Samsung_Cup");
    } else if (cp == AZE_Azerbaijan_Premier) {
      return QString("AZE_Azerbaijan_Premier");
    } else if (cp == AZE_I_Divizion) {
      return QString("AZE_I_Divizion");
    } else if (cp == BEL_Belgian_Jupiler_League) {
      return QString("BEL_Belgian_Jupiler_League");
    } else if (cp == BEL_Belgian_Second_Division) {
      return QString("BEL_Belgian_Second_Division");
    } else if (cp == BEL_Beloften_Pro_League) {
      return QString("BEL_Beloften_Pro_League");
    } else if (cp == BEL_Super_League_women) {
      return QString("BEL_Super_League_women");
    } else if (cp == BGD_Bangladeshi_Premier_League) {
      return QString("BGD_Bangladeshi_Premier_League");
    } else if (cp == BGR_Bulgarian_B_PFG) {
      return QString("BGR_Bulgarian_B_PFG");
    } else if (cp == BGR_Bulgarian_Cup) {
      return QString("BGR_Bulgarian_Cup");
    } else if (cp == BGR_Bulgarian_Premier) {
      return QString("BGR_Bulgarian_Premier");
    } else if (cp == BGR_Bulgarian_Super_Cup) {
      return QString("BGR_Bulgarian_Super_Cup");
    } else if (cp == BGR_Bulgarian_U19_League) {
      return QString("BGR_Bulgarian_U19_League");
    } else if (cp == BHR_Bahrain_FA_Cup) {
      return QString("BHR_Bahrain_FA_Cup");
    } else if (cp == BIH_Bosnian_Premier_League) {
      return QString("BIH_Bosnian_Premier_League");
    } else if (cp == BLR_Belarus_League_W) {
      return QString("BLR_Belarus_League_W");
    } else if (cp == BLR_Belarusian_1st_Division) {
      return QString("BLR_Belarusian_1st_Division");
    } else if (cp == BLR_Belarusian_Premier_League) {
      return QString("BLR_Belarusian_Premier_League");
    } else if (cp == BOL_Bolivian_Liga_Nacional_A) {
      return QString("BOL_Bolivian_Liga_Nacional_A");
    } else if (cp == BRA_Brazil_Carioca_U20) {
      return QString("BRA_Brazil_Carioca_U20");
    } else if (cp == BRA_Brazilian_Cup) {
      return QString("BRA_Brazilian_Cup");
    } else if (cp == BRA_Brazilian_Division_2) {
      return QString("BRA_Brazilian_Division_2");
    } else if (cp == BRA_Brazilian_Paranaense_U19) {
      return QString("BRA_Brazilian_Paranaense_U19");
    } else if (cp == BRA_Brazilian_Serie_C) {
      return QString("BRA_Brazilian_Serie_C");
    } else if (cp == BRA_Brazilian_Serie_D) {
      return QString("BRA_Brazilian_Serie_D");
    } else if (cp == BRA_Brazilian_Taca_FPF) {
      return QString("BRA_Brazilian_Taca_FPF");
    } else if (cp == BRA_Campeonato) {
      return QString("BRA_Campeonato");
    } else if (cp == BRA_Campeonato_Valmir_Louruz) {
      return QString("BRA_Campeonato_Valmir_Louruz");
    } else if (cp == BRA_Copa_Paulista) {
      return QString("BRA_Copa_Paulista");
    } else if (cp == BRA_Copa_Rio) {
      return QString("BRA_Copa_Rio");
    } else if (cp == BRA_Copa_do_Brasil_U20) {
      return QString("BRA_Copa_do_Brasil_U20");
    } else if (cp == BRA_Paulista_U20) {
      return QString("BRA_Paulista_U20");
    } else if (cp == BRA_Serie_C) {
      return QString("BRA_Serie_C");
    } else if (cp == BRA_U20_Championship) {
      return QString("BRA_U20_Championship");
    } else if (cp == BRB_Barbados_Premier_League) {
      return QString("BRB_Barbados_Premier_League");
    } else if (cp == CAF_Champions_League) {
      return QString("CAF_Champions_League");
    } else if (cp == CAN_Canadian_Championship) {
      return QString("CAN_Canadian_Championship");
    } else if (cp == CAN_Canadian_PCSL) {
      return QString("CAN_Canadian_PCSL");
    } else if (cp == CAN_Ontario_League_1) {
      return QString("CAN_Ontario_League_1");
    } else if (cp == CHE_Swiss_Challenge_League) {
      return QString("CHE_Swiss_Challenge_League");
    } else if (cp == CHE_Swiss_Super_League) {
      return QString("CHE_Swiss_Super_League");
    } else if (cp == CHE_Swisscom_Cup) {
      return QString("CHE_Swisscom_Cup");
    } else if (cp == CHL_Chilean_Cup) {
      return QString("CHL_Chilean_Cup");
    } else if (cp == CHL_Chilean_Primera) {
      return QString("CHL_Chilean_Primera");
    } else if (cp == CHL_Chilean_Primera_B) {
      return QString("CHL_Chilean_Primera_B");
    } else if (cp == CHL_Chilean_Segunda_Division) {
      return QString("CHL_Chilean_Segunda_Division");
    } else if (cp == CHN_Chinese_Super_League) {
      return QString("CHN_Chinese_Super_League");
    } else if (cp == COL_Colombian_Primera_A) {
      return QString("COL_Colombian_Primera_A");
    } else if (cp == COL_Colombian_Primera_B) {
      return QString("COL_Colombian_Primera_B");
    } else if (cp == COL_Copa_Colombia) {
      return QString("COL_Copa_Colombia");
    } else if (cp == CRI_Costa_Rican_Primera_Division) {
      return QString("CRI_Costa_Rican_Primera_Division");
    } else if (cp == CZE_1_Liga_Women) {
      return QString("CZE_1_Liga_Women");
    } else if (cp == CZE_Czech_2_Liga) {
      return QString("CZE_Czech_2_Liga");
    } else if (cp == CZE_Czech_3_Liga) {
      return QString("CZE_Czech_3_Liga");
    } else if (cp == CZE_Czech_Republic_Cup) {
      return QString("CZE_Czech_Republic_Cup");
    } else if (cp == CZE_Czech_U19_League) {
      return QString("CZE_Czech_U19_League");
    } else if (cp == CZE_Czech_U21_League) {
      return QString("CZE_Czech_U21_League");
    } else if (cp == CZE_Synot_Liga) {
      return QString("CZE_Synot_Liga");
    } else if (cp == DEU_3_Liga) {
      return QString("DEU_3_Liga");
    } else if (cp == DEU_Bavarian_Cup) {
      return QString("DEU_Bavarian_Cup");
    } else if (cp == DEU_Bundesliga_1) {
      return QString("DEU_Bundesliga_1");
    } else if (cp == DEU_Bundesliga_2) {
      return QString("DEU_Bundesliga_2");
    } else if (cp == DEU_Bundesliga_W) {
      return QString("DEU_Bundesliga_W");
    } else if (cp == DEU_German_Junioren_Bundesliga) {
      return QString("DEU_German_Junioren_Bundesliga");
    } else if (cp == DEU_Regionalliga_Bayern) {
      return QString("DEU_Regionalliga_Bayern");
    } else if (cp == DEU_Regionalliga_Nord) {
      return QString("DEU_Regionalliga_Nord");
    } else if (cp == DEU_Regionalliga_Nordost) {
      return QString("DEU_Regionalliga_Nordost");
    } else if (cp == DEU_Regionalliga_Sudwest) {
      return QString("DEU_Regionalliga_Sudwest");
    } else if (cp == DEU_Regionalliga_West) {
      return QString("DEU_Regionalliga_West");
    } else if (cp == DEU_Westfalenpokal) {
      return QString("DEU_Westfalenpokal");
    } else if (cp == DNK_Danish_Cup) {
      return QString("DNK_Danish_Cup");
    } else if (cp == DNK_Danish_Division_1) {
      return QString("DNK_Danish_Division_1");
    } else if (cp == DNK_Danish_Division_2) {
      return QString("DNK_Danish_Division_2");
    } else if (cp == DNK_Danish_Reserve_League) {
      return QString("DNK_Danish_Reserve_League");
    } else if (cp == DNK_Danish_Superliga) {
      return QString("DNK_Danish_Superliga");
    } else if (cp == DNK_Danish_U19_League) {
      return QString("DNK_Danish_U19_League");
    } else if (cp == DNK_Danish_U21_League) {
      return QString("DNK_Danish_U21_League");
    } else if (cp == DNK_Denmark_Series) {
      return QString("DNK_Denmark_Series");
    } else if (cp == DNK_Division_2_East) {
      return QString("DNK_Division_2_East");
    } else if (cp == DNK_Division_2_West) {
      return QString("DNK_Division_2_West");
    } else if (cp == DNK_Elitedivisionen_W) {
      return QString("DNK_Elitedivisionen_W");
    } else if (cp == DZA_Algerian_Ligue_1) {
      return QString("DZA_Algerian_Ligue_1");
    } else if (cp == DZA_Algerian_U21_Ligue_1) {
      return QString("DZA_Algerian_U21_Ligue_1");
    } else if (cp == DZA_Algerian_U21_Ligue_2) {
      return QString("DZA_Algerian_U21_Ligue_2");
    } else if (cp == ECU_Ecuadorian_Primera_A) {
      return QString("ECU_Ecuadorian_Primera_A");
    } else if (cp == ECU_Ecuadorian_Serie_B) {
      return QString("ECU_Ecuadorian_Serie_B");
    } else if (cp == EGY_Egyptian_Cup) {
      return QString("EGY_Egyptian_Cup");
    } else if (cp == EGY_Egyptian_Premier) {
      return QString("EGY_Egyptian_Premier");
    } else if (cp == ESP_Copa_Catalunya) {
      return QString("ESP_Copa_Catalunya");
    } else if (cp == ESP_Primera_Division) {
      return QString("ESP_Primera_Division");
    } else if (cp == ESP_Primera_Division_W) {
      return QString("ESP_Primera_Division_W");
    } else if (cp == ESP_Segunda_B1) {
      return QString("ESP_Segunda_B1");
    } else if (cp == ESP_Segunda_B2) {
      return QString("ESP_Segunda_B2");
    } else if (cp == ESP_Segunda_B3) {
      return QString("ESP_Segunda_B3");
    } else if (cp == ESP_Segunda_B4) {
      return QString("ESP_Segunda_B4");
    } else if (cp == ESP_Segunda_Division) {
      return QString("ESP_Segunda_Division");
    } else if (cp == ESP_Segunda_Division_women) {
      return QString("ESP_Segunda_Division_women");
    } else if (cp == ESP_Spanish_Copa_Federacion) {
      return QString("ESP_Spanish_Copa_Federacion");
    } else if (cp == ESP_Spanish_Cup) {
      return QString("ESP_Spanish_Cup");
    } else if (cp == ESP_Spanish_Supercup) {
      return QString("ESP_Spanish_Supercup");
    } else if (cp == ESP_Tercera_Division) {
      return QString("ESP_Tercera_Division");
    } else if (cp == EST_Esiliiga_B) {
      return QString("EST_Esiliiga_B");
    } else if (cp == EST_Estonian_Cup) {
      return QString("EST_Estonian_Cup");
    } else if (cp == EST_Estonian_Esiliiga) {
      return QString("EST_Estonian_Esiliiga");
    } else if (cp == EST_Estonian_II_Liga) {
      return QString("EST_Estonian_II_Liga");
    } else if (cp == EST_Estonian_Meistriliiga) {
      return QString("EST_Estonian_Meistriliiga");
    } else if (cp == EST_Estonian_Meistriliiga_Women) {
      return QString("EST_Estonian_Meistriliiga_Women");
    } else if (cp == EST_Estonian_Small_Cup) {
      return QString("EST_Estonian_Small_Cup");
    } else if (cp == FAI_Cup) {
      return QString("FAI_Cup");
    } else if (cp == FIN_Finnish_Cup) {
      return QString("FIN_Finnish_Cup");
    } else if (cp == FIN_Finnish_Kolmonen) {
      return QString("FIN_Finnish_Kolmonen");
    } else if (cp == FIN_Finnish_Naistenliiga_W) {
      return QString("FIN_Finnish_Naistenliiga_W");
    } else if (cp == FIN_Finnish_U19_League) {
      return QString("FIN_Finnish_U19_League");
    } else if (cp == FIN_Kakkonen_East) {
      return QString("FIN_Kakkonen_East");
    } else if (cp == FIN_Kakkonen_North) {
      return QString("FIN_Kakkonen_North");
    } else if (cp == FIN_Kakkonen_South) {
      return QString("FIN_Kakkonen_South");
    } else if (cp == FIN_Kakkonen_West) {
      return QString("FIN_Kakkonen_West");
    } else if (cp == FIN_Veikkausliiga) {
      return QString("FIN_Veikkausliiga");
    } else if (cp == FIN_Ykkonen) {
      return QString("FIN_Ykkonen");
    } else if (cp == FRA_Coupe_de_la_Ligue) {
      return QString("FRA_Coupe_de_la_Ligue");
    } else if (cp == FRA_French_League_W) {
      return QString("FRA_French_League_W");
    } else if (cp == FRA_Ligue_1_Orange) {
      return QString("FRA_Ligue_1_Orange");
    } else if (cp == FRA_Ligue_2_Orange) {
      return QString("FRA_Ligue_2_Orange");
    } else if (cp == FRA_Ligue_National) {
      return QString("FRA_Ligue_National");
    } else if (cp == FRA_Toulon_Tournament) {
      return QString("FRA_Toulon_Tournament");
    } else if (cp == GBR_AFC_Cup) {
      return QString("GBR_AFC_Cup");
    } else if (cp == GBR_Barclays_Premier_League) {
      return QString("GBR_Barclays_Premier_League");
    } else if (cp == GBR_Capital_One_Cup) {
      return QString("GBR_Capital_One_Cup");
    } else if (cp == GBR_English_FA_Cup) {
      return QString("GBR_English_FA_Cup");
    } else if (cp == GBR_Friendlies_W) {
      return QString("GBR_Friendlies_W");
    } else if (cp == GBR_Isthmian_Premier) {
      return QString("GBR_Isthmian_Premier");
    } else if (cp == GBR_Johnstones_Paint_Trophy) {
      return QString("GBR_Johnstones_Paint_Trophy");
    } else if (cp == GBR_Lancashire_Senior_Cup) {
      return QString("GBR_Lancashire_Senior_Cup");
    } else if (cp == GBR_League_One) {
      return QString("GBR_League_One");
    } else if (cp == GBR_League_Two) {
      return QString("GBR_League_Two");
    } else if (cp == GBR_NIFL_Premiership) {
      return QString("GBR_NIFL_Premiership");
    } else if (cp == GBR_NIFL_Reserve_League) {
      return QString("GBR_NIFL_Reserve_League");
    } else if (cp == GBR_National_League) {
      return QString("GBR_National_League");
    } else if (cp == GBR_National_League_North) {
      return QString("GBR_National_League_North");
    } else if (cp == GBR_National_League_South) {
      return QString("GBR_National_League_South");
    } else if (cp == GBR_Northern_Premier) {
      return QString("GBR_Northern_Premier");
    } else if (cp == GBR_Professional_Development_League) {
      return QString("GBR_Professional_Development_League");
    } else if (cp == GBR_SPFL_Development_League) {
      return QString("GBR_SPFL_Development_League");
    } else if (cp == GBR_SPFL_Development_League_2) {
      return QString("GBR_SPFL_Development_League_2");
    } else if (cp == GBR_Scottish_Challenge_Cup) {
      return QString("GBR_Scottish_Challenge_Cup");
    } else if (cp == GBR_Scottish_Championship) {
      return QString("GBR_Scottish_Championship");
    } else if (cp == GBR_Scottish_Cup) {
      return QString("GBR_Scottish_Cup");
    } else if (cp == GBR_Scottish_League_One) {
      return QString("GBR_Scottish_League_One");
    } else if (cp == GBR_Scottish_League_Two) {
      return QString("GBR_Scottish_League_Two");
    } else if (cp == GBR_Scottish_Premiership) {
      return QString("GBR_Scottish_Premiership");
    } else if (cp == GBR_Scottish_SWFL_Women) {
      return QString("GBR_Scottish_SWFL_Women");
    } else if (cp == GBR_Scottish_Womens_Premier_League) {
      return QString("GBR_Scottish_Womens_Premier_League");
    } else if (cp == GBR_Specials) {
      return QString("GBR_Specials");
    } else if (cp == GBR_The_Championship) {
      return QString("GBR_The_Championship");
    } else if (cp == GBR_Welsh_League_Cup) {
      return QString("GBR_Welsh_League_Cup");
    } else if (cp == GBR_Welsh_Premier_League) {
      return QString("GBR_Welsh_Premier_League");
    } else if (cp == GBR_Womens_Super_League) {
      return QString("GBR_Womens_Super_League");
    } else if (cp == GEO_Georgian_Division_1) {
      return QString("GEO_Georgian_Division_1");
    } else if (cp == GEO_Pirveli_Liga) {
      return QString("GEO_Pirveli_Liga");
    } else if (cp == GIB_Gibraltar_Premier_Division) {
      return QString("GIB_Gibraltar_Premier_Division");
    } else if (cp == GRC_Greek_Division_2) {
      return QString("GRC_Greek_Division_2");
    } else if (cp == GRC_Greek_Football_League) {
      return QString("GRC_Greek_Football_League");
    } else if (cp == GRC_Greek_Super_League) {
      return QString("GRC_Greek_Super_League");
    } else if (cp == GRC_Greek_U20_Super_League) {
      return QString("GRC_Greek_U20_Super_League");
    } else if (cp == GTM_Guatemalan_Liga_Nacional) {
      return QString("GTM_Guatemalan_Liga_Nacional");
    } else if (cp == GTM_Guatemalan_Primera_Division_de_Ascenso) {
      return QString("GTM_Guatemalan_Primera_Division_de_Ascenso");
    } else if (cp == HKG_Hong_Kong_Division_1) {
      return QString("HKG_Hong_Kong_Division_1");
    } else if (cp == HND_Liga_Nacional) {
      return QString("HND_Liga_Nacional");
    } else if (cp == HRV_Croatian_3_HNL) {
      return QString("HRV_Croatian_3_HNL");
    } else if (cp == HRV_Croatian_Division_1) {
      return QString("HRV_Croatian_Division_1");
    } else if (cp == HRV_Croatian_Division_2) {
      return QString("HRV_Croatian_Division_2");
    } else if (cp == HRV_Croatian_U19_League) {
      return QString("HRV_Croatian_U19_League");
    } else if (cp == HUN_Hungarian_Cup) {
      return QString("HUN_Hungarian_Cup");
    } else if (cp == HUN_Hungarian_NB_I) {
      return QString("HUN_Hungarian_NB_I");
    } else if (cp == HUN_Hungarian_NB_II) {
      return QString("HUN_Hungarian_NB_II");
    } else if (cp == HUN_Hungarian_NB_I_W) {
      return QString("HUN_Hungarian_NB_I_W");
    } else if (cp == HUN_Hungarian_U19_Division_1) {
      return QString("HUN_Hungarian_U19_Division_1");
    } else if (cp == IDN_Indonesian_Cup) {
      return QString("IDN_Indonesian_Cup");
    } else if (cp == IDN_Presidents_Cup) {
      return QString("IDN_Presidents_Cup");
    } else if (cp == IND_Calcutta_Premier_Division) {
      return QString("IND_Calcutta_Premier_Division");
    } else if (cp == IND_Delhi_Senior_Division) {
      return QString("IND_Delhi_Senior_Division");
    } else if (cp == IND_Goa_Professional_League) {
      return QString("IND_Goa_Professional_League");
    } else if (cp == IND_Indian_Super_League) {
      return QString("IND_Indian_Super_League");
    } else if (cp == IND_Mumbai_Elite_Division_League) {
      return QString("IND_Mumbai_Elite_Division_League");
    } else if (cp == IRL_Airtricity_First_Division) {
      return QString("IRL_Airtricity_First_Division");
    } else if (cp == IRL_Airtricity_Premier_Division) {
      return QString("IRL_Airtricity_Premier_Division");
    } else if (cp == IRL_EA_Sports_Cup) {
      return QString("IRL_EA_Sports_Cup");
    } else if (cp == IRL_FAI_Cup) {
      return QString("IRL_FAI_Cup");
    } else if (cp == ISL_Icelandic_1st_Division_W) {
      return QString("ISL_Icelandic_1st_Division_W");
    } else if (cp == ISL_Icelandic_Cup) {
      return QString("ISL_Icelandic_Cup");
    } else if (cp == ISL_Icelandic_Cup_W) {
      return QString("ISL_Icelandic_Cup_W");
    } else if (cp == ISL_Icelandic_First_Division) {
      return QString("ISL_Icelandic_First_Division");
    } else if (cp == ISL_Icelandic_Fourth_Division) {
      return QString("ISL_Icelandic_Fourth_Division");
    } else if (cp == ISL_Icelandic_Premier_League_W) {
      return QString("ISL_Icelandic_Premier_League_W");
    } else if (cp == ISL_Icelandic_Second_Division) {
      return QString("ISL_Icelandic_Second_Division");
    } else if (cp == ISL_Icelandic_Third_Division) {
      return QString("ISL_Icelandic_Third_Division");
    } else if (cp == ISL_Icelandic_U19_League) {
      return QString("ISL_Icelandic_U19_League");
    } else if (cp == ISL_Icelandic_U19_League_Women) {
      return QString("ISL_Icelandic_U19_League_Women");
    } else if (cp == ISL_Urvalsdeild) {
      return QString("ISL_Urvalsdeild");
    } else if (cp == ISR_Israeli_Liga_Alef) {
      return QString("ISR_Israeli_Liga_Alef");
    } else if (cp == ISR_Israeli_Liga_Leumit) {
      return QString("ISR_Israeli_Liga_Leumit");
    } else if (cp == ISR_Israeli_Liga_Leumit_Cup) {
      return QString("ISR_Israeli_Liga_Leumit_Cup");
    } else if (cp == ISR_Israeli_Premier) {
      return QString("ISR_Israeli_Premier");
    } else if (cp == ISR_Israeli_Premier_League_Cup) {
      return QString("ISR_Israeli_Premier_League_Cup");
    } else if (cp == ISR_Israeli_Super_Cup) {
      return QString("ISR_Israeli_Super_Cup");
    } else if (cp == ISR_Israeli_U19_Elite_Division) {
      return QString("ISR_Israeli_U19_Elite_Division");
    } else if (cp == ITA_Campeonato_Primavera) {
      return QString("ITA_Campeonato_Primavera");
    } else if (cp == ITA_Coppa_Italia) {
      return QString("ITA_Coppa_Italia");
    } else if (cp == ITA_Coppa_Italia_Lega_Pro) {
      return QString("ITA_Coppa_Italia_Lega_Pro");
    } else if (cp == ITA_Lega_Pro) {
      return QString("ITA_Lega_Pro");
    } else if (cp == ITA_Serie_A) {
      return QString("ITA_Serie_A");
    } else if (cp == ITA_Serie_B) {
      return QString("ITA_Serie_B");
    } else if (cp == International_AFC_Champions_League) {
      return QString("International_AFC_Champions_League");
    } else if (cp == International_AFC_Cup) {
      return QString("International_AFC_Cup");
    } else if (cp == International_CAF_African_Cup_of_Nations) {
      return QString("International_CAF_African_Cup_of_Nations");
    } else if (cp == International_CAF_Champions_League) {
      return QString("International_CAF_Champions_League");
    } else if (cp == International_CAF_Confederations_Cup) {
      return QString("International_CAF_Confederations_Cup");
    } else if (cp == International_CONCACAF_Champions_League) {
      return QString("International_CONCACAF_Champions_League");
    } else if (cp == International_Copa_Sudamericana) {
      return QString("International_Copa_Sudamericana");
    } else if (cp == International_Euro_2016) {
      return QString("International_Euro_2016");
    } else if (cp == International_FIFA_World_Cup_2018) {
      return QString("International_FIFA_World_Cup_2018");
    } else if (cp == International_Friendly) {
      return QString("International_Friendly");
    } else if (cp == International_International_Friendly) {
      return QString("International_International_Friendly");
    } else if (cp == International_International_Friendly_W) {
      return QString("International_International_Friendly_W");
    } else if (cp == International_U19_Internationals) {
      return QString("International_U19_Internationals");
    } else if (cp == International_U20_International) {
      return QString("International_U20_International");
    } else if (cp == International_U21_Euro_Championships_Qualifiers) {
      return QString("International_U21_Euro_Championships_Qualifiers");
    } else if (cp == International_U21_International) {
      return QString("International_U21_International");
    } else if (cp == International_UEFA_Champions_League) {
      return QString("International_UEFA_Champions_League");
    } else if (cp == International_UEFA_Europa_League) {
      return QString("International_UEFA_Europa_League");
    } else if (cp == International_UEFA_Youth_League) {
      return QString("International_UEFA_Youth_League");
    } else if (cp == JAM_Jamaican_Premier_League) {
      return QString("JAM_Jamaican_Premier_League");
    } else if (cp == JOR_Jordan_Cup) {
      return QString("JOR_Jordan_Cup");
    } else if (cp == JOR_Jordan_League) {
      return QString("JOR_Jordan_League");
    } else if (cp == JPN_Emperors_Cup) {
      return QString("JPN_Emperors_Cup");
    } else if (cp == JPN_J2_League) {
      return QString("JPN_J2_League");
    } else if (cp == JPN_J3_League) {
      return QString("JPN_J3_League");
    } else if (cp == JPN_J_League) {
      return QString("JPN_J_League");
    } else if (cp == JPN_Japan_Football_League) {
      return QString("JPN_Japan_Football_League");
    } else if (cp == JPN_Japanese_League_W) {
      return QString("JPN_Japanese_League_W");
    } else if (cp == JPN_Nabisco_Cup) {
      return QString("JPN_Nabisco_Cup");
    } else if (cp == KAZ_Kazakhstani_1_Division) {
      return QString("KAZ_Kazakhstani_1_Division");
    } else if (cp == KAZ_Kazakhstani_Premier_League) {
      return QString("KAZ_Kazakhstani_Premier_League");
    } else if (cp == KEN_Kenyan_Premier_League) {
      return QString("KEN_Kenyan_Premier_League");
    } else if (cp == KOR_K_League) {
      return QString("KOR_K_League");
    } else if (cp == LTU_Lithuanian_1_Lyga) {
      return QString("LTU_Lithuanian_1_Lyga");
    } else if (cp == LTU_Lithuanian_A_Lyga) {
      return QString("LTU_Lithuanian_A_Lyga");
    } else if (cp == LTU_Lithuanian_Cup) {
      return QString("LTU_Lithuanian_Cup");
    } else if (cp == LUX_Luxembourg_National_Division) {
      return QString("LUX_Luxembourg_National_Division");
    } else if (cp == LVA_Latvian_1_Liga) {
      return QString("LVA_Latvian_1_Liga");
    } else if (cp == LVA_Latvian_Reserve_League) {
      return QString("LVA_Latvian_Reserve_League");
    } else if (cp == LVA_Latvian_Second_League) {
      return QString("LVA_Latvian_Second_League");
    } else if (cp == LVA_Virsliga) {
      return QString("LVA_Virsliga");
    } else if (cp == MAR_Moroccan_Cup) {
      return QString("MAR_Moroccan_Cup");
    } else if (cp == MAR_Moroccan_Division_1) {
      return QString("MAR_Moroccan_Division_1");
    } else if (cp == MEX_Copa_Mexico) {
      return QString("MEX_Copa_Mexico");
    } else if (cp == MEX_Mexican_Liga_de_Ascenso) {
      return QString("MEX_Mexican_Liga_de_Ascenso");
    } else if (cp == MEX_Mexican_Primera_Division) {
      return QString("MEX_Mexican_Primera_Division");
    } else if (cp == MEX_Mexican_U20_League) {
      return QString("MEX_Mexican_U20_League");
    } else if (cp == MKD_Macedonian_Football_League) {
      return QString("MKD_Macedonian_Football_League");
    } else if (cp == MLS) {
      return QString("MLS");
    } else if (cp == MLT_Maltese_First_Division) {
      return QString("MLT_Maltese_First_Division");
    } else if (cp == MLT_Maltese_Premier_League) {
      return QString("MLT_Maltese_Premier_League");
    } else if (cp == MMR_Myanmar_National_League) {
      return QString("MMR_Myanmar_National_League");
    } else if (cp == MYS_Malaysia_Cup) {
      return QString("MYS_Malaysia_Cup");
    } else if (cp == MYS_Malaysian_Super_League) {
      return QString("MYS_Malaysian_Super_League");
    } else if (cp == NIC_Nicaraguan_Primera_Division) {
      return QString("NIC_Nicaraguan_Primera_Division");
    } else if (cp == NIFL_Premiership) {
      return QString("NIFL_Premiership");
    } else if (cp == NLD_Dutch_Jong_Eredivisie) {
      return QString("NLD_Dutch_Jong_Eredivisie");
    } else if (cp == NLD_Dutch_Jupiler_League) {
      return QString("NLD_Dutch_Jupiler_League");
    } else if (cp == NLD_Eredivisie) {
      return QString("NLD_Eredivisie");
    } else if (cp == NLD_Eredivisie_W) {
      return QString("NLD_Eredivisie_W");
    } else if (cp == NLD_Netherlands_Reserve_League) {
      return QString("NLD_Netherlands_Reserve_League");
    } else if (cp == NOR_Norwegian_1_Division) {
      return QString("NOR_Norwegian_1_Division");
    } else if (cp == NOR_Norwegian_2_Division) {
      return QString("NOR_Norwegian_2_Division");
    } else if (cp == NOR_Norwegian_3_Division) {
      return QString("NOR_Norwegian_3_Division");
    } else if (cp == NOR_Norwegian_Cup) {
      return QString("NOR_Norwegian_Cup");
    } else if (cp == NOR_Norwegian_League_W) {
      return QString("NOR_Norwegian_League_W");
    } else if (cp == NOR_Tippeligaen) {
      return QString("NOR_Tippeligaen");
    } else if (cp == PAN_Panama_Primera_Division) {
      return QString("PAN_Panama_Primera_Division");
    } else if (cp == PER_Peru_Primera_Division) {
      return QString("PER_Peru_Primera_Division");
    } else if (cp == PHL_Philippines_UFL_Cup) {
      return QString("PHL_Philippines_UFL_Cup");
    } else if (cp == PHL_UFL_Division) {
      return QString("PHL_UFL_Division");
    } else if (cp == POL_Ekstraklasa) {
      return QString("POL_Ekstraklasa");
    } else if (cp == POL_Ekstraliga_W) {
      return QString("POL_Ekstraliga_W");
    } else if (cp == POL_Polish_1_Liga) {
      return QString("POL_Polish_1_Liga");
    } else if (cp == POL_Polish_2_Liga) {
      return QString("POL_Polish_2_Liga");
    } else if (cp == POL_Polish_Cup) {
      return QString("POL_Polish_Cup");
    } else if (cp == POL_Polish_U19_Central_Junior_League) {
      return QString("POL_Polish_U19_Central_Junior_League");
    } else if (cp == PRT_Campeonato_Nacional_Seniores) {
      return QString("PRT_Campeonato_Nacional_Seniores");
    } else if (cp == PRT_Portugese_Super_Cup_Women) {
      return QString("PRT_Portugese_Super_Cup_Women");
    } else if (cp == PRT_Portuguese_U19_Championship) {
      return QString("PRT_Portuguese_U19_Championship");
    } else if (cp == PRT_Primeira_Liga) {
      return QString("PRT_Primeira_Liga");
    } else if (cp == PRT_Segunda_Liga) {
      return QString("PRT_Segunda_Liga");
    } else if (cp == PRT_Taca_da_Liga) {
      return QString("PRT_Taca_da_Liga");
    } else if (cp == PRT_Taca_de_Portugal) {
      return QString("PRT_Taca_de_Portugal");
    } else if (cp == PRY_Paraguayan_Primera) {
      return QString("PRY_Paraguayan_Primera");
    } else if (cp == QAT_Qatari_Stars_League) {
      return QString("QAT_Qatari_Stars_League");
    } else if (cp == ROU_Liga_1) {
      return QString("ROU_Liga_1");
    } else if (cp == ROU_Romanian_Cup) {
      return QString("ROU_Romanian_Cup");
    } else if (cp == ROU_Romanian_Liga_II) {
      return QString("ROU_Romanian_Liga_II");
    } else if (cp == ROU_Romanian_Liga_III) {
      return QString("ROU_Romanian_Liga_III");
    } else if (cp == RUS_Premier_Division) {
      return QString("RUS_Premier_Division");
    } else if (cp == RUS_Russian_Cup) {
      return QString("RUS_Russian_Cup");
    } else if (cp == RUS_Russian_Division_1) {
      return QString("RUS_Russian_Division_1");
    } else if (cp == RUS_Russian_Division_2) {
      return QString("RUS_Russian_Division_2");
    } else if (cp == RUS_Russian_Regional_Leagues) {
      return QString("RUS_Russian_Regional_Leagues");
    } else if (cp == RUS_Russian_Youth_League) {
      return QString("RUS_Russian_Youth_League");
    } else if (cp == SAU_Saudi_Crown_Prince_Cup) {
      return QString("SAU_Saudi_Crown_Prince_Cup");
    } else if (cp == SAU_Saudi_Premier) {
      return QString("SAU_Saudi_Premier");
    } else if (cp == SGP_Singapore_Cup) {
      return QString("SGP_Singapore_Cup");
    } else if (cp == SGP_Singapore_Prime_League) {
      return QString("SGP_Singapore_Prime_League");
    } else if (cp == SGP_Singapore_S_League) {
      return QString("SGP_Singapore_S_League");
    } else if (cp == SLV_El_Salvadoran_Primera_Division) {
      return QString("SLV_El_Salvadoran_Primera_Division");
    } else if (cp == SRB_Serbian_Super_Liga) {
      return QString("SRB_Serbian_Super_Liga");
    } else if (cp == SVK_1_Liga_East) {
      return QString("SVK_1_Liga_East");
    } else if (cp == SVK_1_Liga_West) {
      return QString("SVK_1_Liga_West");
    } else if (cp == SVK_Slovakian_1_Liga) {
      return QString("SVK_Slovakian_1_Liga");
    } else if (cp == SVK_Slovakian_Cup) {
      return QString("SVK_Slovakian_Cup");
    } else if (cp == SVK_Slovakian_Super_Liga) {
      return QString("SVK_Slovakian_Super_Liga");
    } else if (cp == SVK_Slovakian_U19_League) {
      return QString("SVK_Slovakian_U19_League");
    } else if (cp == SVN_2_SNL) {
      return QString("SVN_2_SNL");
    } else if (cp == SVN_Slovenian_Prva_Liga) {
      return QString("SVN_Slovenian_Prva_Liga");
    } else if (cp == SWE_Allsvenskan) {
      return QString("SWE_Allsvenskan");
    } else if (cp == SWE_Superettan) {
      return QString("SWE_Superettan");
    } else if (cp == SWE_Swedish_Cup) {
      return QString("SWE_Swedish_Cup");
    } else if (cp == SWE_Swedish_Div_1_Norra) {
      return QString("SWE_Swedish_Div_1_Norra");
    } else if (cp == SWE_Swedish_Div_1_Sodra) {
      return QString("SWE_Swedish_Div_1_Sodra");
    } else if (cp == SWE_Swedish_Division_1_W) {
      return QString("SWE_Swedish_Division_1_W");
    } else if (cp == SWE_Swedish_Division_2) {
      return QString("SWE_Swedish_Division_2");
    } else if (cp == THA_Thailand_Division_1) {
      return QString("THA_Thailand_Division_1");
    } else if (cp == THA_Thailand_Division_2) {
      return QString("THA_Thailand_Division_2");
    } else if (cp == THA_Thailand_FA_Cup) {
      return QString("THA_Thailand_FA_Cup");
    } else if (cp == THA_Thailand_League_Cup) {
      return QString("THA_Thailand_League_Cup");
    } else if (cp == THA_Thailand_Premier_League) {
      return QString("THA_Thailand_Premier_League");
    } else if (cp == TUN_Tunisian_Cup) {
      return QString("TUN_Tunisian_Cup");
    } else if (cp == TUN_Tunisian_Ligue_Professionelle_1) {
      return QString("TUN_Tunisian_Ligue_Professionelle_1");
    } else if (cp == TUR_Turkish_Division_1) {
      return QString("TUR_Turkish_Division_1");
    } else if (cp == TUR_Turkish_Super_League) {
      return QString("TUR_Turkish_Super_League");
    } else if (cp == UEFA_Champions_League) {
      return QString("UEFA_Champions_League");
    } else if (cp == UEFA_Europa_League) {
      return QString("UEFA_Europa_League");
    } else if (cp == UKR_Ukrainian_Cup) {
      return QString("UKR_Ukrainian_Cup");
    } else if (cp == UKR_Ukrainian_Druha_Liga) {
      return QString("UKR_Ukrainian_Druha_Liga");
    } else if (cp == UKR_Ukrainian_League_W) {
      return QString("UKR_Ukrainian_League_W");
    } else if (cp == UKR_Ukrainian_Persha_Liga) {
      return QString("UKR_Ukrainian_Persha_Liga");
    } else if (cp == UKR_Ukrainian_U19_League) {
      return QString("UKR_Ukrainian_U19_League");
    } else if (cp == UKR_Ukrainian_U21_League) {
      return QString("UKR_Ukrainian_U21_League");
    } else if (cp == UKR_Vischya_Liga) {
      return QString("UKR_Vischya_Liga");
    } else if (cp == URY_Uruguayan_Primera) {
      return QString("URY_Uruguayan_Primera");
    } else if (cp == URY_Uruguayan_Segunda_Division) {
      return QString("URY_Uruguayan_Segunda_Division");
    } else if (cp == USA_MLS) {
      return QString("USA_MLS");
    } else if (cp == USA_NPSL) {
      return QString("USA_NPSL");
    } else if (cp == USA_North_American_Soccer_League) {
      return QString("USA_North_American_Soccer_League");
    } else if (cp == USA_USL_Pro) {
      return QString("USA_USL_Pro");
    } else if (cp == USA_US_Open_Cup) {
      return QString("USA_US_Open_Cup");
    } else if (cp == USA_US_PDL) {
      return QString("USA_US_PDL");
    } else if (cp == USL_Pro) {
      return QString("USL_Pro");
    } else if (cp == UZB_Uzbekistan_1_Division) {
      return QString("UZB_Uzbekistan_1_Division");
    } else if (cp == UZB_Uzbekistan_Cup) {
      return QString("UZB_Uzbekistan_Cup");
    } else if (cp == UZB_Uzbekistan_Professional_League) {
      return QString("UZB_Uzbekistan_Professional_League");
    } else if (cp == UZB_Uzbekistan_Youth_League_U23) {
      return QString("UZB_Uzbekistan_Youth_League_U23");
    } else if (cp == VEN_Copa_Venezuela) {
      return QString("VEN_Copa_Venezuela");
    } else if (cp == VEN_Liga_de_Ascenso) {
      return QString("VEN_Liga_de_Ascenso");
    } else if (cp == VEN_Venezuelan_Primera) {
      return QString("VEN_Venezuelan_Primera");
    } else if (cp == VNM_National_Cup) {
      return QString("VNM_National_Cup");
    } else if (cp == VNM_VLeague_1) {
      return QString("VNM_VLeague_1");
    } else if (cp == VNM_VLeague_2) {
      return QString("VNM_VLeague_2");
    } else if (cp == ZAF_8_Cup) {
      return QString("ZAF_8_Cup");
    } else if (cp == ZAF_Premier_Soccer_League) {
      return QString("ZAF_Premier_Soccer_League");
    } else if (cp == ZAF_South_African_First_Division) {
      return QString("ZAF_South_African_First_Division");
    } else if (cp == ZAF_South_African_League_Cup) {
      return QString("ZAF_South_African_League_Cup");
    } else if (cp == ZAF_South_African_Varsity_Football_Challenge) {
      return QString("ZAF_South_African_Varsity_Football_Challenge");
    }
    return QString("UNDEFINED");
  }
  static Competition toEnum(int val) {
    if (val == -1) {
      return ALL;
    } else if (val == -2) {
      return UNKOWN;
    } else if (val == 309972) {
      return AFC_Cup;
    } else if (val == 309972) {
      return AFC_Cup;
    } else if (val == 4039797) {
      return ARE_UAE_Emirates_Cup_Group_Stage;
    } else if (val == 258537) {
      return ARE_UAE_Premier_League;
    } else if (val == 3765124) {
      return ARG_Argentinian_Primera_B_Metropolitana;
    } else if (val == 803237) {
      return ARG_Argentinian_Primera_B_Nacional;
    } else if (val == 7511144) {
      return ARG_Argentinian_Primera_C_Metropolitana;
    } else if (val == 67387) {
      return ARG_Argentinian_Primera_Division;
    } else if (val == 1227903) {
      return ARG_Copa_Argentina;
    } else if (val == 7617364) {
      return ARG_Torneo_Federal_A;
    } else if (val == 3061353) {
      return ARM_Armenian_First_League;
    } else if (val == 2888729) {
      return ARM_Armenian_Premier_League;
    } else if (val == 7) {
      return AUT_Austrian_Bundesliga;
    } else if (val == 7593578) {
      return AUT_Austrian_OFB_Ladies_Cup;
    } else if (val == 7317506) {
      return AUT_Austrian_Regionalliga;
    } else if (val == 9) {
      return AUT_Erste_Liga;
    } else if (val == 167716) {
      return AUT_Samsung_Cup;
    } else if (val == 895129) {
      return AZE_Azerbaijan_Premier;
    } else if (val == 4517491) {
      return AZE_I_Divizion;
    } else if (val == 89979) {
      return BEL_Belgian_Jupiler_League;
    } else if (val == 164952) {
      return BEL_Belgian_Second_Division;
    } else if (val == 3037492) {
      return BEL_Beloften_Pro_League;
    } else if (val == 8189587) {
      return BEL_Super_League_women;
    } else if (val == 5388369) {
      return BGD_Bangladeshi_Premier_League;
    } else if (val == 5618298) {
      return BGR_Bulgarian_B_PFG;
    } else if (val == 309948) {
      return BGR_Bulgarian_Cup;
    } else if (val == 15) {
      return BGR_Bulgarian_Premier;
    } else if (val == 338432) {
      return BGR_Bulgarian_Super_Cup;
    } else if (val == 8211415) {
      return BGR_Bulgarian_U19_League;
    } else if (val == 1478090) {
      return BHR_Bahrain_FA_Cup;
    } else if (val == 3127357) {
      return BIH_Bosnian_Premier_League;
    } else if (val == 1079277) {
      return BLR_Belarus_League_W;
    } else if (val == 3126267) {
      return BLR_Belarusian_1st_Division;
    } else if (val == 888275) {
      return BLR_Belarusian_Premier_League;
    } else if (val == 3729355) {
      return BOL_Bolivian_Liga_Nacional_A;
    } else if (val == 7425648) {
      return BRA_Brazil_Carioca_U20;
    } else if (val == 89219) {
      return BRA_Brazilian_Cup;
    } else if (val == 321319) {
      return BRA_Brazilian_Division_2;
    } else if (val == 7717120) {
      return BRA_Brazilian_Paranaense_U19;
    } else if (val == 3172302) {
      return BRA_Brazilian_Serie_C;
    } else if (val == 7980087) {
      return BRA_Brazilian_Serie_D;
    } else if (val == 7883210) {
      return BRA_Brazilian_Taca_FPF;
    } else if (val == 13) {
      return BRA_Campeonato;
    } else if (val == 8011625) {
      return BRA_Campeonato_Valmir_Louruz;
    } else if (val == 3583988) {
      return BRA_Copa_Paulista;
    } else if (val == 5982310) {
      return BRA_Copa_Rio;
    } else if (val == 3744990) {
      return BRA_Copa_do_Brasil_U20;
    } else if (val == 3127716) {
      return BRA_Paulista_U20;
    } else if (val == 3172302) {
      return BRA_Serie_C;
    } else if (val == 804633) {
      return BRA_U20_Championship;
    } else if (val == 4644792) {
      return BRB_Barbados_Premier_League;
    } else if (val == 987643) {
      return CAF_Champions_League;
    } else if (val == 908099) {
      return CAN_Canadian_Championship;
    } else if (val == 5389244) {
      return CAN_Canadian_PCSL;
    } else if (val == 5339687) {
      return CAN_Ontario_League_1;
    } else if (val == 135) {
      return CHE_Swiss_Challenge_League;
    } else if (val == 133) {
      return CHE_Swiss_Super_League;
    } else if (val == 29051) {
      return CHE_Swisscom_Cup;
    } else if (val == 961354) {
      return CHL_Chilean_Cup;
    } else if (val == 744098) {
      return CHL_Chilean_Primera;
    } else if (val == 857992) {
      return CHL_Chilean_Primera_B;
    } else if (val == 3085749) {
      return CHL_Chilean_Segunda_Division;
    } else if (val == 879931) {
      return CHN_Chinese_Super_League;
    } else if (val == 844197) {
      return COL_Colombian_Primera_A;
    } else if (val == 856134) {
      return COL_Colombian_Primera_B;
    } else if (val == 854148) {
      return COL_Copa_Colombia;
    } else if (val == 2079376) {
      return CRI_Costa_Rican_Primera_Division;
    } else if (val == 3765192) {
      return CZE_1_Liga_Women;
    } else if (val == 862638) {
      return CZE_Czech_2_Liga;
    } else if (val == 892425) {
      return CZE_Czech_3_Liga;
    } else if (val == 97807) {
      return CZE_Czech_Republic_Cup;
    } else if (val == 1987477) {
      return CZE_Czech_U19_League;
    } else if (val == 4848838) {
      return CZE_Czech_U21_League;
    } else if (val == 21) {
      return CZE_Synot_Liga;
    } else if (val == 158146) {
      return DEU_3_Liga;
    } else if (val == 7152675) {
      return DEU_Bavarian_Cup;
    } else if (val == 59) {
      return DEU_Bundesliga_1;
    } else if (val == 61) {
      return DEU_Bundesliga_2;
    } else if (val == 6294253) {
      return DEU_Bundesliga_W;
    } else if (val == 852459) {
      return DEU_German_Junioren_Bundesliga;
    } else if (val == 853948) {
      return DEU_Regionalliga_Bayern;
    } else if (val == 63) {
      return DEU_Regionalliga_Nord;
    } else if (val == 318343) {
      return DEU_Regionalliga_Nordost;
    } else if (val == 65) {
      return DEU_Regionalliga_Sudwest;
    } else if (val == 840808) {
      return DEU_Regionalliga_West;
    } else if (val == 1242586) {
      return DEU_Westfalenpokal;
    } else if (val == 30921) {
      return DNK_Danish_Cup;
    } else if (val == 25) {
      return DNK_Danish_Division_1;
    } else if (val == 7998231) {
      return DNK_Danish_Division_2;
    } else if (val == 858294) {
      return DNK_Danish_Reserve_League;
    } else if (val == 23) {
      return DNK_Danish_Superliga;
    } else if (val == 940730) {
      return DNK_Danish_U19_League;
    } else if (val == 886334) {
      return DNK_Danish_U21_League;
    } else if (val == 8244827) {
      return DNK_Denmark_Series;
    } else if (val == 29) {
      return DNK_Division_2_East;
    } else if (val == 27) {
      return DNK_Division_2_West;
    } else if (val == 3221347) {
      return DNK_Elitedivisionen_W;
    } else if (val == 4431442) {
      return DZA_Algerian_Ligue_1;
    } else if (val == 3792498) {
      return DZA_Algerian_U21_Ligue_1;
    } else if (val == 4556663) {
      return DZA_Algerian_U21_Ligue_2;
    } else if (val == 803690) {
      return ECU_Ecuadorian_Primera_A;
    } else if (val == 3057583) {
      return ECU_Ecuadorian_Serie_B;
    } else if (val == 802004) {
      return EGY_Egyptian_Cup;
    } else if (val == 801976) {
      return EGY_Egyptian_Premier;
    } else if (val == 1032778) {
      return ESP_Copa_Catalunya;
    } else if (val == 117) {
      return ESP_Primera_Division;
    } else if (val == 6362364) {
      return ESP_Primera_Division_W;
    } else if (val == 121) {
      return ESP_Segunda_B1;
    } else if (val == 123) {
      return ESP_Segunda_B2;
    } else if (val == 125) {
      return ESP_Segunda_B3;
    } else if (val == 127) {
      return ESP_Segunda_B4;
    } else if (val == 119) {
      return ESP_Segunda_Division;
    } else if (val == 4608262) {
      return ESP_Segunda_Division_women;
    } else if (val == 834025) {
      return ESP_Spanish_Copa_Federacion;
    } else if (val == 12801) {
      return ESP_Spanish_Cup;
    } else if (val == 584) {
      return ESP_Spanish_Supercup;
    } else if (val == 821269) {
      return ESP_Tercera_Division;
    } else if (val == 2901699) {
      return EST_Esiliiga_B;
    } else if (val == 886734) {
      return EST_Estonian_Cup;
    } else if (val == 873203) {
      return EST_Estonian_Esiliiga;
    } else if (val == 5699678) {
      return EST_Estonian_II_Liga;
    } else if (val == 862545) {
      return EST_Estonian_Meistriliiga;
    } else if (val == 3221481) {
      return EST_Estonian_Meistriliiga_Women;
    } else if (val == 7594575) {
      return EST_Estonian_Small_Cup;
    } else if (val == 7485811) {
      return FAI_Cup;
    } else if (val == 20601) {
      return FIN_Finnish_Cup;
    } else if (val == 5281887) {
      return FIN_Finnish_Kolmonen;
    } else if (val == 982877) {
      return FIN_Finnish_Naistenliiga_W;
    } else if (val == 1684210) {
      return FIN_Finnish_U19_League;
    } else if (val == 53) {
      return FIN_Kakkonen_East;
    } else if (val == 51) {
      return FIN_Kakkonen_North;
    } else if (val == 49) {
      return FIN_Kakkonen_South;
    } else if (val == 1551845) {
      return FIN_Kakkonen_West;
    } else if (val == 45) {
      return FIN_Veikkausliiga;
    } else if (val == 47) {
      return FIN_Ykkonen;
    } else if (val == 22358) {
      return FRA_Coupe_de_la_Ligue;
    } else if (val == 6023868) {
      return FRA_French_League_W;
    } else if (val == 55) {
      return FRA_Ligue_1_Orange;
    } else if (val == 57) {
      return FRA_Ligue_2_Orange;
    } else if (val == 1081960) {
      return FRA_Ligue_National;
    } else if (val == 91729) {
      return FRA_Toulon_Tournament;
    } else if (val == 309972) {
      return GBR_AFC_Cup;
    } else if (val == 31) {
      return GBR_Barclays_Premier_League;
    } else if (val == 2134) {
      return GBR_Capital_One_Cup;
    } else if (val == 30558) {
      return GBR_English_FA_Cup;
    } else if (val == 4684340) {
      return GBR_Friendlies_W;
    } else if (val == 820582) {
      return GBR_Isthmian_Premier;
    } else if (val == 24789) {
      return GBR_Johnstones_Paint_Trophy;
    } else if (val == 1279245) {
      return GBR_Lancashire_Senior_Cup;
    } else if (val == 35) {
      return GBR_League_One;
    } else if (val == 37) {
      return GBR_League_Two;
    } else if (val == 20351) {
      return GBR_NIFL_Premiership;
    } else if (val == 4540650) {
      return GBR_NIFL_Reserve_League;
    } else if (val == 39) {
      return GBR_National_League;
    } else if (val == 41) {
      return GBR_National_League_North;
    } else if (val == 43) {
      return GBR_National_League_South;
    } else if (val == 820753) {
      return GBR_Northern_Premier;
    } else if (val == 2129602) {
      return GBR_Professional_Development_League;
    } else if (val == 5808320) {
      return GBR_SPFL_Development_League;
    } else if (val == 6011072) {
      return GBR_SPFL_Development_League_2;
    } else if (val == 334679) {
      return GBR_Scottish_Challenge_Cup;
    } else if (val == 107) {
      return GBR_Scottish_Championship;
    } else if (val == 409743) {
      return GBR_Scottish_Cup;
    } else if (val == 109) {
      return GBR_Scottish_League_One;
    } else if (val == 111) {
      return GBR_Scottish_League_Two;
    } else if (val == 105) {
      return GBR_Scottish_Premiership;
    } else if (val == 7672495) {
      return GBR_Scottish_SWFL_Women;
    } else if (val == 7552802) {
      return GBR_Scottish_Womens_Premier_League;
    } else if (val == 2608550) {
      return GBR_Specials;
    } else if (val == 7129730) {
      return GBR_The_Championship;
    } else if (val == 695030) {
      return GBR_Welsh_League_Cup;
    } else if (val == 252549) {
      return GBR_Welsh_Premier_League;
    } else if (val == 887470) {
      return GBR_Womens_Super_League;
    } else if (val == 4040072) {
      return GEO_Georgian_Division_1;
    } else if (val == 2356065) {
      return GEO_Pirveli_Liga;
    } else if (val == 6182297) {
      return GIB_Gibraltar_Premier_Division;
    } else if (val == 69) {
      return GRC_Greek_Division_2;
    } else if (val == 833616) {
      return GRC_Greek_Football_League;
    } else if (val == 67) {
      return GRC_Greek_Super_League;
    } else if (val == 824417) {
      return GRC_Greek_U20_Super_League;
    } else if (val == 6566654) {
      return GTM_Guatemalan_Liga_Nacional;
    } else if (val == 6812603) {
      return GTM_Guatemalan_Primera_Division_de_Ascenso;
    } else if (val == 833990) {
      return HKG_Hong_Kong_Division_1;
    } else if (val == 4517524) {
      return HND_Liga_Nacional;
    } else if (val == 7596190) {
      return HRV_Croatian_3_HNL;
    } else if (val == 17) {
      return HRV_Croatian_Division_1;
    } else if (val == 3992967) {
      return HRV_Croatian_Division_2;
    } else if (val == 3765131) {
      return HRV_Croatian_U19_League;
    } else if (val == 94603) {
      return HUN_Hungarian_Cup;
    } else if (val == 1842928) {
      return HUN_Hungarian_NB_I;
    } else if (val == 4556576) {
      return HUN_Hungarian_NB_II;
    } else if (val == 8211299) {
      return HUN_Hungarian_NB_I_W;
    } else if (val == 311575) {
      return HUN_Hungarian_U19_Division_1;
    } else if (val == 8085064) {
      return IDN_Indonesian_Cup;
    } else if (val == 845150) {
      return IDN_Presidents_Cup;
    } else if (val == 2462835) {
      return IND_Calcutta_Premier_Division;
    } else if (val == 7995514) {
      return IND_Delhi_Senior_Division;
    } else if (val == 3781558) {
      return IND_Goa_Professional_League;
    } else if (val == 6251219) {
      return IND_Indian_Super_League;
    } else if (val == 5007039) {
      return IND_Mumbai_Elite_Division_League;
    } else if (val == 79) {
      return IRL_Airtricity_First_Division;
    } else if (val == 77) {
      return IRL_Airtricity_Premier_Division;
    } else if (val == 24865) {
      return IRL_EA_Sports_Cup;
    } else if (val == 7485811) {
      return IRL_FAI_Cup;
    } else if (val == 984404) {
      return ISL_Icelandic_1st_Division_W;
    } else if (val == 154811) {
      return ISL_Icelandic_Cup;
    } else if (val == 827084) {
      return ISL_Icelandic_Cup_W;
    } else if (val == 905441) {
      return ISL_Icelandic_First_Division;
    } else if (val == 5618314) {
      return ISL_Icelandic_Fourth_Division;
    } else if (val == 911286) {
      return ISL_Icelandic_Premier_League_W;
    } else if (val == 943450) {
      return ISL_Icelandic_Second_Division;
    } else if (val == 3126286) {
      return ISL_Icelandic_Third_Division;
    } else if (val == 907589) {
      return ISL_Icelandic_U19_League;
    } else if (val == 3244094) {
      return ISL_Icelandic_U19_League_Women;
    } else if (val == 887158) {
      return ISL_Urvalsdeild;
    } else if (val == 5618479) {
      return ISR_Israeli_Liga_Alef;
    } else if (val == 804044) {
      return ISR_Israeli_Liga_Leumit;
    } else if (val == 1035449) {
      return ISR_Israeli_Liga_Leumit_Cup;
    } else if (val == 822165) {
      return ISR_Israeli_Premier;
    } else if (val == 1161205) {
      return ISR_Israeli_Premier_League_Cup;
    } else if (val == 8083549) {
      return ISR_Israeli_Super_Cup;
    } else if (val == 2465205) {
      return ISR_Israeli_U19_Elite_Division;
    } else if (val == 841133) {
      return ITA_Campeonato_Primavera;
    } else if (val == 1874) {
      return ITA_Coppa_Italia;
    } else if (val == 849268) {
      return ITA_Coppa_Italia_Lega_Pro;
    } else if (val == 5984496) {
      return ITA_Lega_Pro;
    } else if (val == 81) {
      return ITA_Serie_A;
    } else if (val == 83) {
      return ITA_Serie_B;
    } else if (val == 39218) {
      return International_AFC_Champions_League;
    } else if (val == 309972) {
      return International_AFC_Cup;
    } else if (val == 4254855) {
      return International_CAF_African_Cup_of_Nations;
    } else if (val == 987643) {
      return International_CAF_Champions_League;
    } else if (val == 2001733) {
      return International_CAF_Confederations_Cup;
    } else if (val == 194961) {
      return International_CONCACAF_Champions_League;
    } else if (val == 4655) {
      return International_Copa_Sudamericana;
    } else if (val == 4527196) {
      return International_Euro_2016;
    } else if (val == 5614746) {
      return International_FIFA_World_Cup_2018;
    } else if (val == 219) {
      return International_Friendly;
    } else if (val == 1985077) {
      return International_International_Friendly;
    } else if (val == 88832) {
      return International_International_Friendly_W;
    } else if (val == 13051) {
      return International_U19_Internationals;
    } else if (val == 402969) {
      return International_U20_International;
    } else if (val == 7597618) {
      return International_U21_Euro_Championships_Qualifiers;
    } else if (val == 6301) {
      return International_U21_International;
    } else if (val == 228) {
      return International_UEFA_Champions_League;
    } else if (val == 2005) {
      return International_UEFA_Europa_League;
    } else if (val == 3784863) {
      return International_UEFA_Youth_League;
    } else if (val == 3796898) {
      return JAM_Jamaican_Premier_League;
    } else if (val == 900926) {
      return JOR_Jordan_Cup;
    } else if (val == 843222) {
      return JOR_Jordan_League;
    } else if (val == 236552) {
      return JPN_Emperors_Cup;
    } else if (val == 1062024) {
      return JPN_J2_League;
    } else if (val == 4802285) {
      return JPN_J3_League;
    } else if (val == 89) {
      return JPN_J_League;
    } else if (val == 3785366) {
      return JPN_Japan_Football_League;
    } else if (val == 7143446) {
      return JPN_Japanese_League_W;
    } else if (val == 32518) {
      return JPN_Nabisco_Cup;
    } else if (val == 3297851) {
      return KAZ_Kazakhstani_1_Division;
    } else if (val == 3127737) {
      return KAZ_Kazakhstani_Premier_League;
    } else if (val == 7616742) {
      return KEN_Kenyan_Premier_League;
    } else if (val == 867459) {
      return KOR_K_League;
    } else if (val == 1587980) {
      return LTU_Lithuanian_1_Lyga;
    } else if (val == 879221) {
      return LTU_Lithuanian_A_Lyga;
    } else if (val == 1147862) {
      return LTU_Lithuanian_Cup;
    } else if (val == 4515700) {
      return LUX_Luxembourg_National_Division;
    } else if (val == 1661891) {
      return LVA_Latvian_1_Liga;
    } else if (val == 7183687) {
      return LVA_Latvian_Reserve_League;
    } else if (val == 3242305) {
      return LVA_Latvian_Second_League;
    } else if (val == 887178) {
      return LVA_Virsliga;
    } else if (val == 4095837) {
      return MAR_Moroccan_Cup;
    } else if (val == 2609677) {
      return MAR_Moroccan_Division_1;
    } else if (val == 1979279) {
      return MEX_Copa_Mexico;
    } else if (val == 827754) {
      return MEX_Mexican_Liga_de_Ascenso;
    } else if (val == 5627174) {
      return MEX_Mexican_Primera_Division;
    } else if (val == 827078) {
      return MEX_Mexican_U20_League;
    } else if (val == 1517121) {
      return MKD_Macedonian_Football_League;
    } else if (val == 141) {
      return MLS;
    } else if (val == 2923434) {
      return MLT_Maltese_First_Division;
    } else if (val == 1327393) {
      return MLT_Maltese_Premier_League;
    } else if (val == 7836682) {
      return MMR_Myanmar_National_League;
    } else if (val == 1105022) {
      return MYS_Malaysia_Cup;
    } else if (val == 840886) {
      return MYS_Malaysian_Super_League;
    } else if (val == 6480193) {
      return NIC_Nicaraguan_Primera_Division;
    } else if (val == 20351) {
      return NIFL_Premiership;
    } else if (val == 836645) {
      return NLD_Dutch_Jong_Eredivisie;
    } else if (val == 11) {
      return NLD_Dutch_Jupiler_League;
    } else if (val == 71) {
      return NLD_Eredivisie;
    } else if (val == 8139939) {
      return NLD_Eredivisie_W;
    } else if (val == 8068520) {
      return NLD_Netherlands_Reserve_League;
    } else if (val == 95) {
      return NOR_Norwegian_1_Division;
    } else if (val == 891106) {
      return NOR_Norwegian_2_Division;
    } else if (val == 920858) {
      return NOR_Norwegian_3_Division;
    } else if (val == 4051) {
      return NOR_Norwegian_Cup;
    } else if (val == 7126020) {
      return NOR_Norwegian_League_W;
    } else if (val == 93) {
      return NOR_Tippeligaen;
    } else if (val == 3972877) {
      return PAN_Panama_Primera_Division;
    } else if (val == 848082) {
      return PER_Peru_Primera_Division;
    } else if (val == 7319790) {
      return PHL_Philippines_UFL_Cup;
    } else if (val == 6871833) {
      return PHL_UFL_Division;
    } else if (val == 97) {
      return POL_Ekstraklasa;
    } else if (val == 7138694) {
      return POL_Ekstraliga_W;
    } else if (val == 403085) {
      return POL_Polish_1_Liga;
    } else if (val == 876442) {
      return POL_Polish_2_Liga;
    } else if (val == 32246) {
      return POL_Polish_Cup;
    } else if (val == 5449376) {
      return POL_Polish_U19_Central_Junior_League;
    } else if (val == 4517616) {
      return PRT_Campeonato_Nacional_Seniores;
    } else if (val == 8166570) {
      return PRT_Portugese_Super_Cup_Women;
    } else if (val == 863810) {
      return PRT_Portuguese_U19_Championship;
    } else if (val == 99) {
      return PRT_Primeira_Liga;
    } else if (val == 9513) {
      return PRT_Segunda_Liga;
    } else if (val == 19640) {
      return PRT_Taca_da_Liga;
    } else if (val == 61351) {
      return PRT_Taca_de_Portugal;
    } else if (val == 839575) {
      return PRY_Paraguayan_Primera;
    } else if (val == 842258) {
      return QAT_Qatari_Stars_League;
    } else if (val == 4905) {
      return ROU_Liga_1;
    } else if (val == 218756) {
      return ROU_Romanian_Cup;
    } else if (val == 862579) {
      return ROU_Romanian_Liga_II;
    } else if (val == 3006957) {
      return ROU_Romanian_Liga_III;
    } else if (val == 101) {
      return RUS_Premier_Division;
    } else if (val == 33051) {
      return RUS_Russian_Cup;
    } else if (val == 880458) {
      return RUS_Russian_Division_1;
    } else if (val == 891179) {
      return RUS_Russian_Division_2;
    } else if (val == 7425130) {
      return RUS_Russian_Regional_Leagues;
    } else if (val == 868392) {
      return RUS_Russian_Youth_League;
    } else if (val == 840912) {
      return SAU_Saudi_Crown_Prince_Cup;
    } else if (val == 853446) {
      return SAU_Saudi_Premier;
    } else if (val == 944127) {
      return SGP_Singapore_Cup;
    } else if (val == 868823) {
      return SGP_Singapore_Prime_League;
    } else if (val == 848322) {
      return SGP_Singapore_S_League;
    } else if (val == 4802204) {
      return SLV_El_Salvadoran_Primera_Division;
    } else if (val == 103) {
      return SRB_Serbian_Super_Liga;
    } else if (val == 5714159) {
      return SVK_1_Liga_East;
    } else if (val == 5713494) {
      return SVK_1_Liga_West;
    } else if (val == 2938065) {
      return SVK_Slovakian_1_Liga;
    } else if (val == 97855) {
      return SVK_Slovakian_Cup;
    } else if (val == 113) {
      return SVK_Slovakian_Super_Liga;
    } else if (val == 872270) {
      return SVK_Slovakian_U19_League;
    } else if (val == 8141281) {
      return SVN_2_SNL;
    } else if (val == 115) {
      return SVN_Slovenian_Prva_Liga;
    } else if (val == 129) {
      return SWE_Allsvenskan;
    } else if (val == 131) {
      return SWE_Superettan;
    } else if (val == 18099) {
      return SWE_Swedish_Cup;
    } else if (val == 500102) {
      return SWE_Swedish_Div_1_Norra;
    } else if (val == 500180) {
      return SWE_Swedish_Div_1_Sodra;
    } else if (val == 7261893) {
      return SWE_Swedish_Division_1_W;
    } else if (val == 920223) {
      return SWE_Swedish_Division_2;
    } else if (val == 4608858) {
      return THA_Thailand_Division_1;
    } else if (val == 4608865) {
      return THA_Thailand_Division_2;
    } else if (val == 3297875) {
      return THA_Thailand_FA_Cup;
    } else if (val == 5448752) {
      return THA_Thailand_League_Cup;
    } else if (val == 3332575) {
      return THA_Thailand_Premier_League;
    } else if (val == 6390405) {
      return TUN_Tunisian_Cup;
    } else if (val == 6103298) {
      return TUN_Tunisian_Ligue_Professionelle_1;
    } else if (val == 175680) {
      return TUR_Turkish_Division_1;
    } else if (val == 194215) {
      return TUR_Turkish_Super_League;
    } else if (val == 228) {
      return UEFA_Champions_League;
    } else if (val == 2005) {
      return UEFA_Europa_League;
    } else if (val == 300965) {
      return UKR_Ukrainian_Cup;
    } else if (val == 1658999) {
      return UKR_Ukrainian_Druha_Liga;
    } else if (val == 3089001) {
      return UKR_Ukrainian_League_W;
    } else if (val == 872215) {
      return UKR_Ukrainian_Persha_Liga;
    } else if (val == 1888360) {
      return UKR_Ukrainian_U19_League;
    } else if (val == 7946082) {
      return UKR_Ukrainian_U21_League;
    } else if (val == 139) {
      return UKR_Vischya_Liga;
    } else if (val == 843454) {
      return URY_Uruguayan_Primera;
    } else if (val == 6104087) {
      return URY_Uruguayan_Segunda_Division;
    } else if (val == 141) {
      return USA_MLS;
    } else if (val == 5618531) {
      return USA_NPSL;
    } else if (val == 156320) {
      return USA_North_American_Soccer_League;
    } else if (val == 3004992) {
      return USA_USL_Pro;
    } else if (val == 155369) {
      return USA_US_Open_Cup;
    } else if (val == 7465669) {
      return USA_US_PDL;
    } else if (val == 3004992) {
      return USL_Pro;
    } else if (val == 7197874) {
      return UZB_Uzbekistan_1_Division;
    } else if (val == 4851739) {
      return UZB_Uzbekistan_Cup;
    } else if (val == 908196) {
      return UZB_Uzbekistan_Professional_League;
    } else if (val == 4732508) {
      return UZB_Uzbekistan_Youth_League_U23;
    } else if (val == 7893771) {
      return VEN_Copa_Venezuela;
    } else if (val == 7897688) {
      return VEN_Liga_de_Ascenso;
    } else if (val == 1065530) {
      return VEN_Venezuelan_Primera;
    } else if (val == 4608119) {
      return VNM_National_Cup;
    } else if (val == 4555345) {
      return VNM_VLeague_1;
    } else if (val == 5326228) {
      return VNM_VLeague_2;
    } else if (val == 5790028) {
      return ZAF_8_Cup;
    } else if (val == 2631619) {
      return ZAF_Premier_Soccer_League;
    } else if (val == 3785359) {
      return ZAF_South_African_First_Division;
    } else if (val == 6197407) {
      return ZAF_South_African_League_Cup;
    } else if (val == 7942109) {
      return ZAF_South_African_Varsity_Football_Challenge;
    }
    return UNKOWN;
  }
  static std::list<Competition> oneList() {
    std::list<Competition> theList;
    theList.push_back(AFC_Cup);
    theList.push_back(ARE_UAE_Emirates_Cup_Group_Stage);
    theList.push_back(ARE_UAE_Premier_League);
    theList.push_back(ARG_Argentinian_Primera_B_Metropolitana);
    theList.push_back(ARG_Argentinian_Primera_B_Nacional);
    theList.push_back(ARG_Argentinian_Primera_C_Metropolitana);
    theList.push_back(ARG_Argentinian_Primera_Division);
    theList.push_back(ARG_Copa_Argentina);
    theList.push_back(ARG_Torneo_Federal_A);
    theList.push_back(ARM_Armenian_First_League);
    theList.push_back(ARM_Armenian_Premier_League);
    theList.push_back(AUT_Austrian_Bundesliga);
    theList.push_back(AUT_Austrian_OFB_Ladies_Cup);
    theList.push_back(AUT_Austrian_Regionalliga);
    theList.push_back(AUT_Erste_Liga);
    theList.push_back(AUT_Samsung_Cup);
    theList.push_back(AZE_Azerbaijan_Premier);
    theList.push_back(AZE_I_Divizion);
    theList.push_back(BEL_Belgian_Jupiler_League);
    theList.push_back(BEL_Belgian_Second_Division);
    theList.push_back(BEL_Beloften_Pro_League);
    theList.push_back(BEL_Super_League_women);
    theList.push_back(BGD_Bangladeshi_Premier_League);
    theList.push_back(BGR_Bulgarian_B_PFG);
    theList.push_back(BGR_Bulgarian_Cup);
    theList.push_back(BGR_Bulgarian_Premier);
    theList.push_back(BGR_Bulgarian_Super_Cup);
    theList.push_back(BGR_Bulgarian_U19_League);
    theList.push_back(BHR_Bahrain_FA_Cup);
    theList.push_back(BIH_Bosnian_Premier_League);
    theList.push_back(BLR_Belarus_League_W);
    theList.push_back(BLR_Belarusian_1st_Division);
    theList.push_back(BLR_Belarusian_Premier_League);
    theList.push_back(BOL_Bolivian_Liga_Nacional_A);
    theList.push_back(BRA_Brazil_Carioca_U20);
    theList.push_back(BRA_Brazilian_Cup);
    theList.push_back(BRA_Brazilian_Division_2);
    theList.push_back(BRA_Brazilian_Paranaense_U19);
    theList.push_back(BRA_Brazilian_Serie_C);
    theList.push_back(BRA_Brazilian_Serie_D);
    theList.push_back(BRA_Brazilian_Taca_FPF);
    theList.push_back(BRA_Campeonato);
    theList.push_back(BRA_Campeonato_Valmir_Louruz);
    theList.push_back(BRA_Copa_Paulista);
    theList.push_back(BRA_Copa_Rio);
    theList.push_back(BRA_Copa_do_Brasil_U20);
    theList.push_back(BRA_Paulista_U20);
    theList.push_back(BRA_Serie_C);
    theList.push_back(BRA_U20_Championship);
    theList.push_back(BRB_Barbados_Premier_League);
    theList.push_back(CAF_Champions_League);
    theList.push_back(CAN_Canadian_Championship);
    theList.push_back(CAN_Canadian_PCSL);
    theList.push_back(CAN_Ontario_League_1);
    theList.push_back(CHE_Swiss_Challenge_League);
    theList.push_back(CHE_Swiss_Super_League);
    theList.push_back(CHE_Swisscom_Cup);
    theList.push_back(CHL_Chilean_Cup);
    theList.push_back(CHL_Chilean_Primera);
    theList.push_back(CHL_Chilean_Primera_B);
    theList.push_back(CHL_Chilean_Segunda_Division);
    theList.push_back(CHN_Chinese_Super_League);
    theList.push_back(COL_Colombian_Primera_A);
    theList.push_back(COL_Colombian_Primera_B);
    theList.push_back(COL_Copa_Colombia);
    theList.push_back(CRI_Costa_Rican_Primera_Division);
    theList.push_back(CZE_1_Liga_Women);
    theList.push_back(CZE_Czech_2_Liga);
    theList.push_back(CZE_Czech_3_Liga);
    theList.push_back(CZE_Czech_Republic_Cup);
    theList.push_back(CZE_Czech_U19_League);
    theList.push_back(CZE_Czech_U21_League);
    theList.push_back(CZE_Synot_Liga);
    theList.push_back(DEU_3_Liga);
    theList.push_back(DEU_Bavarian_Cup);
    theList.push_back(DEU_Bundesliga_1);
    theList.push_back(DEU_Bundesliga_2);
    theList.push_back(DEU_Bundesliga_W);
    theList.push_back(DEU_German_Junioren_Bundesliga);
    theList.push_back(DEU_Regionalliga_Bayern);
    theList.push_back(DEU_Regionalliga_Nord);
    theList.push_back(DEU_Regionalliga_Nordost);
    theList.push_back(DEU_Regionalliga_Sudwest);
    theList.push_back(DEU_Regionalliga_West);
    theList.push_back(DEU_Westfalenpokal);
    theList.push_back(DNK_Danish_Cup);
    theList.push_back(DNK_Danish_Division_1);
    theList.push_back(DNK_Danish_Division_2);
    theList.push_back(DNK_Danish_Reserve_League);
    theList.push_back(DNK_Danish_Superliga);
    theList.push_back(DNK_Danish_U19_League);
    theList.push_back(DNK_Danish_U21_League);
    theList.push_back(DNK_Denmark_Series);
    theList.push_back(DNK_Division_2_East);
    theList.push_back(DNK_Division_2_West);
    theList.push_back(DNK_Elitedivisionen_W);
    theList.push_back(DZA_Algerian_Ligue_1);
    theList.push_back(DZA_Algerian_U21_Ligue_1);
    theList.push_back(DZA_Algerian_U21_Ligue_2);
    theList.push_back(ECU_Ecuadorian_Primera_A);
    theList.push_back(ECU_Ecuadorian_Serie_B);
    theList.push_back(EGY_Egyptian_Cup);
    theList.push_back(EGY_Egyptian_Premier);
    theList.push_back(ESP_Copa_Catalunya);
    theList.push_back(ESP_Primera_Division);
    theList.push_back(ESP_Primera_Division_W);
    theList.push_back(ESP_Segunda_B1);
    theList.push_back(ESP_Segunda_B2);
    theList.push_back(ESP_Segunda_B3);
    theList.push_back(ESP_Segunda_B4);
    theList.push_back(ESP_Segunda_Division);
    theList.push_back(ESP_Segunda_Division_women);
    theList.push_back(ESP_Spanish_Copa_Federacion);
    theList.push_back(ESP_Spanish_Cup);
    theList.push_back(ESP_Spanish_Supercup);
    theList.push_back(ESP_Tercera_Division);
    theList.push_back(EST_Esiliiga_B);
    theList.push_back(EST_Estonian_Cup);
    theList.push_back(EST_Estonian_Esiliiga);
    theList.push_back(EST_Estonian_II_Liga);
    theList.push_back(EST_Estonian_Meistriliiga);
    theList.push_back(EST_Estonian_Meistriliiga_Women);
    theList.push_back(EST_Estonian_Small_Cup);
    theList.push_back(FAI_Cup);
    theList.push_back(FIN_Finnish_Cup);
    theList.push_back(FIN_Finnish_Kolmonen);
    theList.push_back(FIN_Finnish_Naistenliiga_W);
    theList.push_back(FIN_Finnish_U19_League);
    theList.push_back(FIN_Kakkonen_East);
    theList.push_back(FIN_Kakkonen_North);
    theList.push_back(FIN_Kakkonen_South);
    theList.push_back(FIN_Kakkonen_West);
    theList.push_back(FIN_Veikkausliiga);
    theList.push_back(FIN_Ykkonen);
    theList.push_back(FRA_Coupe_de_la_Ligue);
    theList.push_back(FRA_French_League_W);
    theList.push_back(FRA_Ligue_1_Orange);
    theList.push_back(FRA_Ligue_2_Orange);
    theList.push_back(FRA_Ligue_National);
    theList.push_back(FRA_Toulon_Tournament);
    theList.push_back(GBR_AFC_Cup);
    theList.push_back(GBR_Barclays_Premier_League);
    theList.push_back(GBR_Capital_One_Cup);
    theList.push_back(GBR_English_FA_Cup);
    theList.push_back(GBR_Friendlies_W);
    theList.push_back(GBR_Isthmian_Premier);
    theList.push_back(GBR_Johnstones_Paint_Trophy);
    theList.push_back(GBR_Lancashire_Senior_Cup);
    theList.push_back(GBR_League_One);
    theList.push_back(GBR_League_Two);
    theList.push_back(GBR_NIFL_Premiership);
    theList.push_back(GBR_NIFL_Reserve_League);
    theList.push_back(GBR_National_League);
    theList.push_back(GBR_National_League_North);
    theList.push_back(GBR_National_League_South);
    theList.push_back(GBR_Northern_Premier);
    theList.push_back(GBR_Professional_Development_League);
    theList.push_back(GBR_SPFL_Development_League);
    theList.push_back(GBR_SPFL_Development_League_2);
    theList.push_back(GBR_Scottish_Challenge_Cup);
    theList.push_back(GBR_Scottish_Championship);
    theList.push_back(GBR_Scottish_Cup);
    theList.push_back(GBR_Scottish_League_One);
    theList.push_back(GBR_Scottish_League_Two);
    theList.push_back(GBR_Scottish_Premiership);
    theList.push_back(GBR_Scottish_SWFL_Women);
    theList.push_back(GBR_Scottish_Womens_Premier_League);
    theList.push_back(GBR_Specials);
    theList.push_back(GBR_The_Championship);
    theList.push_back(GBR_Welsh_League_Cup);
    theList.push_back(GBR_Welsh_Premier_League);
    theList.push_back(GBR_Womens_Super_League);
    theList.push_back(GEO_Georgian_Division_1);
    theList.push_back(GEO_Pirveli_Liga);
    theList.push_back(GIB_Gibraltar_Premier_Division);
    theList.push_back(GRC_Greek_Division_2);
    theList.push_back(GRC_Greek_Football_League);
    theList.push_back(GRC_Greek_Super_League);
    theList.push_back(GRC_Greek_U20_Super_League);
    theList.push_back(GTM_Guatemalan_Liga_Nacional);
    theList.push_back(GTM_Guatemalan_Primera_Division_de_Ascenso);
    theList.push_back(HKG_Hong_Kong_Division_1);
    theList.push_back(HND_Liga_Nacional);
    theList.push_back(HRV_Croatian_3_HNL);
    theList.push_back(HRV_Croatian_Division_1);
    theList.push_back(HRV_Croatian_Division_2);
    theList.push_back(HRV_Croatian_U19_League);
    theList.push_back(HUN_Hungarian_Cup);
    theList.push_back(HUN_Hungarian_NB_I);
    theList.push_back(HUN_Hungarian_NB_II);
    theList.push_back(HUN_Hungarian_NB_I_W);
    theList.push_back(HUN_Hungarian_U19_Division_1);
    theList.push_back(IDN_Indonesian_Cup);
    theList.push_back(IDN_Presidents_Cup);
    theList.push_back(IND_Calcutta_Premier_Division);
    theList.push_back(IND_Delhi_Senior_Division);
    theList.push_back(IND_Goa_Professional_League);
    theList.push_back(IND_Indian_Super_League);
    theList.push_back(IND_Mumbai_Elite_Division_League);
    theList.push_back(IRL_Airtricity_First_Division);
    theList.push_back(IRL_Airtricity_Premier_Division);
    theList.push_back(IRL_EA_Sports_Cup);
    theList.push_back(IRL_FAI_Cup);
    theList.push_back(ISL_Icelandic_1st_Division_W);
    theList.push_back(ISL_Icelandic_Cup);
    theList.push_back(ISL_Icelandic_Cup_W);
    theList.push_back(ISL_Icelandic_First_Division);
    theList.push_back(ISL_Icelandic_Fourth_Division);
    theList.push_back(ISL_Icelandic_Premier_League_W);
    theList.push_back(ISL_Icelandic_Second_Division);
    theList.push_back(ISL_Icelandic_Third_Division);
    theList.push_back(ISL_Icelandic_U19_League);
    theList.push_back(ISL_Icelandic_U19_League_Women);
    theList.push_back(ISL_Urvalsdeild);
    theList.push_back(ISR_Israeli_Liga_Alef);
    theList.push_back(ISR_Israeli_Liga_Leumit);
    theList.push_back(ISR_Israeli_Liga_Leumit_Cup);
    theList.push_back(ISR_Israeli_Premier);
    theList.push_back(ISR_Israeli_Premier_League_Cup);
    theList.push_back(ISR_Israeli_Super_Cup);
    theList.push_back(ISR_Israeli_U19_Elite_Division);
    theList.push_back(ITA_Campeonato_Primavera);
    theList.push_back(ITA_Coppa_Italia);
    theList.push_back(ITA_Coppa_Italia_Lega_Pro);
    theList.push_back(ITA_Lega_Pro);
    theList.push_back(ITA_Serie_A);
    theList.push_back(ITA_Serie_B);
    theList.push_back(International_AFC_Champions_League);
    theList.push_back(International_AFC_Cup);
    theList.push_back(International_CAF_African_Cup_of_Nations);
    theList.push_back(International_CAF_Champions_League);
    theList.push_back(International_CAF_Confederations_Cup);
    theList.push_back(International_CONCACAF_Champions_League);
    theList.push_back(International_Copa_Sudamericana);
    theList.push_back(International_Euro_2016);
    theList.push_back(International_FIFA_World_Cup_2018);
    theList.push_back(International_Friendly);
    theList.push_back(International_International_Friendly);
    theList.push_back(International_International_Friendly_W);
    theList.push_back(International_U19_Internationals);
    theList.push_back(International_U20_International);
    theList.push_back(International_U21_Euro_Championships_Qualifiers);
    theList.push_back(International_U21_International);
    theList.push_back(International_UEFA_Champions_League);
    theList.push_back(International_UEFA_Europa_League);
    theList.push_back(International_UEFA_Youth_League);
    theList.push_back(JAM_Jamaican_Premier_League);
    theList.push_back(JOR_Jordan_Cup);
    theList.push_back(JOR_Jordan_League);
    theList.push_back(JPN_Emperors_Cup);
    theList.push_back(JPN_J2_League);
    theList.push_back(JPN_J3_League);
    theList.push_back(JPN_J_League);
    theList.push_back(JPN_Japan_Football_League);
    theList.push_back(JPN_Japanese_League_W);
    theList.push_back(JPN_Nabisco_Cup);
    theList.push_back(KAZ_Kazakhstani_1_Division);
    theList.push_back(KAZ_Kazakhstani_Premier_League);
    theList.push_back(KEN_Kenyan_Premier_League);
    theList.push_back(KOR_K_League);
    theList.push_back(LTU_Lithuanian_1_Lyga);
    theList.push_back(LTU_Lithuanian_A_Lyga);
    theList.push_back(LTU_Lithuanian_Cup);
    theList.push_back(LUX_Luxembourg_National_Division);
    theList.push_back(LVA_Latvian_1_Liga);
    theList.push_back(LVA_Latvian_Reserve_League);
    theList.push_back(LVA_Latvian_Second_League);
    theList.push_back(LVA_Virsliga);
    theList.push_back(MAR_Moroccan_Cup);
    theList.push_back(MAR_Moroccan_Division_1);
    theList.push_back(MEX_Copa_Mexico);
    theList.push_back(MEX_Mexican_Liga_de_Ascenso);
    theList.push_back(MEX_Mexican_Primera_Division);
    theList.push_back(MEX_Mexican_U20_League);
    theList.push_back(MKD_Macedonian_Football_League);
    theList.push_back(MLS);
    theList.push_back(MLT_Maltese_First_Division);
    theList.push_back(MLT_Maltese_Premier_League);
    theList.push_back(MMR_Myanmar_National_League);
    theList.push_back(MYS_Malaysia_Cup);
    theList.push_back(MYS_Malaysian_Super_League);
    theList.push_back(NIC_Nicaraguan_Primera_Division);
    theList.push_back(NIFL_Premiership);
    theList.push_back(NLD_Dutch_Jong_Eredivisie);
    theList.push_back(NLD_Dutch_Jupiler_League);
    theList.push_back(NLD_Eredivisie);
    theList.push_back(NLD_Eredivisie_W);
    theList.push_back(NLD_Netherlands_Reserve_League);
    theList.push_back(NOR_Norwegian_1_Division);
    theList.push_back(NOR_Norwegian_2_Division);
    theList.push_back(NOR_Norwegian_3_Division);
    theList.push_back(NOR_Norwegian_Cup);
    theList.push_back(NOR_Norwegian_League_W);
    theList.push_back(NOR_Tippeligaen);
    theList.push_back(PAN_Panama_Primera_Division);
    theList.push_back(PER_Peru_Primera_Division);
    theList.push_back(PHL_Philippines_UFL_Cup);
    theList.push_back(PHL_UFL_Division);
    theList.push_back(POL_Ekstraklasa);
    theList.push_back(POL_Ekstraliga_W);
    theList.push_back(POL_Polish_1_Liga);
    theList.push_back(POL_Polish_2_Liga);
    theList.push_back(POL_Polish_Cup);
    theList.push_back(POL_Polish_U19_Central_Junior_League);
    theList.push_back(PRT_Campeonato_Nacional_Seniores);
    theList.push_back(PRT_Portugese_Super_Cup_Women);
    theList.push_back(PRT_Portuguese_U19_Championship);
    theList.push_back(PRT_Primeira_Liga);
    theList.push_back(PRT_Segunda_Liga);
    theList.push_back(PRT_Taca_da_Liga);
    theList.push_back(PRT_Taca_de_Portugal);
    theList.push_back(PRY_Paraguayan_Primera);
    theList.push_back(QAT_Qatari_Stars_League);
    theList.push_back(ROU_Liga_1);
    theList.push_back(ROU_Romanian_Cup);
    theList.push_back(ROU_Romanian_Liga_II);
    theList.push_back(ROU_Romanian_Liga_III);
    theList.push_back(RUS_Premier_Division);
    theList.push_back(RUS_Russian_Cup);
    theList.push_back(RUS_Russian_Division_1);
    theList.push_back(RUS_Russian_Division_2);
    theList.push_back(RUS_Russian_Regional_Leagues);
    theList.push_back(RUS_Russian_Youth_League);
    theList.push_back(SAU_Saudi_Crown_Prince_Cup);
    theList.push_back(SAU_Saudi_Premier);
    theList.push_back(SGP_Singapore_Cup);
    theList.push_back(SGP_Singapore_Prime_League);
    theList.push_back(SGP_Singapore_S_League);
    theList.push_back(SLV_El_Salvadoran_Primera_Division);
    theList.push_back(SRB_Serbian_Super_Liga);
    theList.push_back(SVK_1_Liga_East);
    theList.push_back(SVK_1_Liga_West);
    theList.push_back(SVK_Slovakian_1_Liga);
    theList.push_back(SVK_Slovakian_Cup);
    theList.push_back(SVK_Slovakian_Super_Liga);
    theList.push_back(SVK_Slovakian_U19_League);
    theList.push_back(SVN_2_SNL);
    theList.push_back(SVN_Slovenian_Prva_Liga);
    theList.push_back(SWE_Allsvenskan);
    theList.push_back(SWE_Superettan);
    theList.push_back(SWE_Swedish_Cup);
    theList.push_back(SWE_Swedish_Div_1_Norra);
    theList.push_back(SWE_Swedish_Div_1_Sodra);
    theList.push_back(SWE_Swedish_Division_1_W);
    theList.push_back(SWE_Swedish_Division_2);
    theList.push_back(THA_Thailand_Division_1);
    theList.push_back(THA_Thailand_Division_2);
    theList.push_back(THA_Thailand_FA_Cup);
    theList.push_back(THA_Thailand_League_Cup);
    theList.push_back(THA_Thailand_Premier_League);
    theList.push_back(TUN_Tunisian_Cup);
    theList.push_back(TUN_Tunisian_Ligue_Professionelle_1);
    theList.push_back(TUR_Turkish_Division_1);
    theList.push_back(TUR_Turkish_Super_League);
    theList.push_back(UEFA_Champions_League);
    theList.push_back(UEFA_Europa_League);
    theList.push_back(UKR_Ukrainian_Cup);
    theList.push_back(UKR_Ukrainian_Druha_Liga);
    theList.push_back(UKR_Ukrainian_League_W);
    theList.push_back(UKR_Ukrainian_Persha_Liga);
    theList.push_back(UKR_Ukrainian_U19_League);
    theList.push_back(UKR_Ukrainian_U21_League);
    theList.push_back(UKR_Vischya_Liga);
    theList.push_back(URY_Uruguayan_Primera);
    theList.push_back(URY_Uruguayan_Segunda_Division);
    theList.push_back(USA_MLS);
    theList.push_back(USA_NPSL);
    theList.push_back(USA_North_American_Soccer_League);
    theList.push_back(USA_USL_Pro);
    theList.push_back(USA_US_Open_Cup);
    theList.push_back(USA_US_PDL);
    theList.push_back(USL_Pro);
    theList.push_back(UZB_Uzbekistan_1_Division);
    theList.push_back(UZB_Uzbekistan_Cup);
    theList.push_back(UZB_Uzbekistan_Professional_League);
    theList.push_back(UZB_Uzbekistan_Youth_League_U23);
    theList.push_back(VEN_Copa_Venezuela);
    theList.push_back(VEN_Liga_de_Ascenso);
    theList.push_back(VEN_Venezuelan_Primera);
    theList.push_back(VNM_National_Cup);
    theList.push_back(VNM_VLeague_1);
    theList.push_back(VNM_VLeague_2);
    theList.push_back(ZAF_8_Cup);
    theList.push_back(ZAF_Premier_Soccer_League);
    theList.push_back(ZAF_South_African_First_Division);
    theList.push_back(ZAF_South_African_League_Cup);
    theList.push_back(ZAF_South_African_Varsity_Football_Challenge);
    return theList;
  }
  static std::list<Competition> twoListSplit(int side) {
    std::list<Competition> theList1;
    std::list<Competition> theList2;
    theList1.push_back(AFC_Cup);
    theList2.push_back(ARE_UAE_Emirates_Cup_Group_Stage);
    theList1.push_back(ARE_UAE_Premier_League);
    theList2.push_back(ARG_Argentinian_Primera_B_Metropolitana);
    theList1.push_back(ARG_Argentinian_Primera_B_Nacional);
    theList2.push_back(ARG_Argentinian_Primera_C_Metropolitana);
    theList1.push_back(ARG_Argentinian_Primera_Division);
    theList2.push_back(ARG_Copa_Argentina);
    theList1.push_back(ARG_Torneo_Federal_A);
    theList2.push_back(ARM_Armenian_First_League);
    theList1.push_back(ARM_Armenian_Premier_League);
    theList2.push_back(AUT_Austrian_Bundesliga);
    theList1.push_back(AUT_Austrian_OFB_Ladies_Cup);
    theList2.push_back(AUT_Austrian_Regionalliga);
    theList1.push_back(AUT_Erste_Liga);
    theList2.push_back(AUT_Samsung_Cup);
    theList1.push_back(AZE_Azerbaijan_Premier);
    theList2.push_back(AZE_I_Divizion);
    theList1.push_back(BEL_Belgian_Jupiler_League);
    theList2.push_back(BEL_Belgian_Second_Division);
    theList1.push_back(BEL_Beloften_Pro_League);
    theList2.push_back(BEL_Super_League_women);
    theList1.push_back(BGD_Bangladeshi_Premier_League);
    theList2.push_back(BGR_Bulgarian_B_PFG);
    theList1.push_back(BGR_Bulgarian_Cup);
    theList2.push_back(BGR_Bulgarian_Premier);
    theList1.push_back(BGR_Bulgarian_Super_Cup);
    theList2.push_back(BGR_Bulgarian_U19_League);
    theList1.push_back(BHR_Bahrain_FA_Cup);
    theList2.push_back(BIH_Bosnian_Premier_League);
    theList1.push_back(BLR_Belarus_League_W);
    theList2.push_back(BLR_Belarusian_1st_Division);
    theList1.push_back(BLR_Belarusian_Premier_League);
    theList2.push_back(BOL_Bolivian_Liga_Nacional_A);
    theList1.push_back(BRA_Brazil_Carioca_U20);
    theList2.push_back(BRA_Brazilian_Cup);
    theList1.push_back(BRA_Brazilian_Division_2);
    theList2.push_back(BRA_Brazilian_Paranaense_U19);
    theList1.push_back(BRA_Brazilian_Serie_C);
    theList2.push_back(BRA_Brazilian_Serie_D);
    theList1.push_back(BRA_Brazilian_Taca_FPF);
    theList2.push_back(BRA_Campeonato);
    theList1.push_back(BRA_Campeonato_Valmir_Louruz);
    theList2.push_back(BRA_Copa_Paulista);
    theList1.push_back(BRA_Copa_Rio);
    theList2.push_back(BRA_Copa_do_Brasil_U20);
    theList1.push_back(BRA_Paulista_U20);
    theList2.push_back(BRA_Serie_C);
    theList1.push_back(BRA_U20_Championship);
    theList2.push_back(BRB_Barbados_Premier_League);
    theList1.push_back(CAF_Champions_League);
    theList2.push_back(CAN_Canadian_Championship);
    theList1.push_back(CAN_Canadian_PCSL);
    theList2.push_back(CAN_Ontario_League_1);
    theList1.push_back(CHE_Swiss_Challenge_League);
    theList2.push_back(CHE_Swiss_Super_League);
    theList1.push_back(CHE_Swisscom_Cup);
    theList2.push_back(CHL_Chilean_Cup);
    theList1.push_back(CHL_Chilean_Primera);
    theList2.push_back(CHL_Chilean_Primera_B);
    theList1.push_back(CHL_Chilean_Segunda_Division);
    theList2.push_back(CHN_Chinese_Super_League);
    theList1.push_back(COL_Colombian_Primera_A);
    theList2.push_back(COL_Colombian_Primera_B);
    theList1.push_back(COL_Copa_Colombia);
    theList2.push_back(CRI_Costa_Rican_Primera_Division);
    theList1.push_back(CZE_1_Liga_Women);
    theList2.push_back(CZE_Czech_2_Liga);
    theList1.push_back(CZE_Czech_3_Liga);
    theList2.push_back(CZE_Czech_Republic_Cup);
    theList1.push_back(CZE_Czech_U19_League);
    theList2.push_back(CZE_Czech_U21_League);
    theList1.push_back(CZE_Synot_Liga);
    theList2.push_back(DEU_3_Liga);
    theList1.push_back(DEU_Bavarian_Cup);
    theList2.push_back(DEU_Bundesliga_1);
    theList1.push_back(DEU_Bundesliga_2);
    theList2.push_back(DEU_Bundesliga_W);
    theList1.push_back(DEU_German_Junioren_Bundesliga);
    theList2.push_back(DEU_Regionalliga_Bayern);
    theList1.push_back(DEU_Regionalliga_Nord);
    theList2.push_back(DEU_Regionalliga_Nordost);
    theList1.push_back(DEU_Regionalliga_Sudwest);
    theList2.push_back(DEU_Regionalliga_West);
    theList1.push_back(DEU_Westfalenpokal);
    theList2.push_back(DNK_Danish_Cup);
    theList1.push_back(DNK_Danish_Division_1);
    theList2.push_back(DNK_Danish_Division_2);
    theList1.push_back(DNK_Danish_Reserve_League);
    theList2.push_back(DNK_Danish_Superliga);
    theList1.push_back(DNK_Danish_U19_League);
    theList2.push_back(DNK_Danish_U21_League);
    theList1.push_back(DNK_Denmark_Series);
    theList2.push_back(DNK_Division_2_East);
    theList1.push_back(DNK_Division_2_West);
    theList2.push_back(DNK_Elitedivisionen_W);
    theList1.push_back(DZA_Algerian_Ligue_1);
    theList2.push_back(DZA_Algerian_U21_Ligue_1);
    theList1.push_back(DZA_Algerian_U21_Ligue_2);
    theList2.push_back(ECU_Ecuadorian_Primera_A);
    theList1.push_back(ECU_Ecuadorian_Serie_B);
    theList2.push_back(EGY_Egyptian_Cup);
    theList1.push_back(EGY_Egyptian_Premier);
    theList2.push_back(ESP_Copa_Catalunya);
    theList1.push_back(ESP_Primera_Division);
    theList2.push_back(ESP_Primera_Division_W);
    theList1.push_back(ESP_Segunda_B1);
    theList2.push_back(ESP_Segunda_B2);
    theList1.push_back(ESP_Segunda_B3);
    theList2.push_back(ESP_Segunda_B4);
    theList1.push_back(ESP_Segunda_Division);
    theList2.push_back(ESP_Segunda_Division_women);
    theList1.push_back(ESP_Spanish_Copa_Federacion);
    theList2.push_back(ESP_Spanish_Cup);
    theList1.push_back(ESP_Spanish_Supercup);
    theList2.push_back(ESP_Tercera_Division);
    theList1.push_back(EST_Esiliiga_B);
    theList2.push_back(EST_Estonian_Cup);
    theList1.push_back(EST_Estonian_Esiliiga);
    theList2.push_back(EST_Estonian_II_Liga);
    theList1.push_back(EST_Estonian_Meistriliiga);
    theList2.push_back(EST_Estonian_Meistriliiga_Women);
    theList1.push_back(EST_Estonian_Small_Cup);
    theList2.push_back(FAI_Cup);
    theList1.push_back(FIN_Finnish_Cup);
    theList2.push_back(FIN_Finnish_Kolmonen);
    theList1.push_back(FIN_Finnish_Naistenliiga_W);
    theList2.push_back(FIN_Finnish_U19_League);
    theList1.push_back(FIN_Kakkonen_East);
    theList2.push_back(FIN_Kakkonen_North);
    theList1.push_back(FIN_Kakkonen_South);
    theList2.push_back(FIN_Kakkonen_West);
    theList1.push_back(FIN_Veikkausliiga);
    theList2.push_back(FIN_Ykkonen);
    theList1.push_back(FRA_Coupe_de_la_Ligue);
    theList2.push_back(FRA_French_League_W);
    theList1.push_back(FRA_Ligue_1_Orange);
    theList2.push_back(FRA_Ligue_2_Orange);
    theList1.push_back(FRA_Ligue_National);
    theList2.push_back(FRA_Toulon_Tournament);
    theList1.push_back(GBR_AFC_Cup);
    theList2.push_back(GBR_Barclays_Premier_League);
    theList1.push_back(GBR_Capital_One_Cup);
    theList2.push_back(GBR_English_FA_Cup);
    theList1.push_back(GBR_Friendlies_W);
    theList2.push_back(GBR_Isthmian_Premier);
    theList1.push_back(GBR_Johnstones_Paint_Trophy);
    theList2.push_back(GBR_Lancashire_Senior_Cup);
    theList1.push_back(GBR_League_One);
    theList2.push_back(GBR_League_Two);
    theList1.push_back(GBR_NIFL_Premiership);
    theList2.push_back(GBR_NIFL_Reserve_League);
    theList1.push_back(GBR_National_League);
    theList2.push_back(GBR_National_League_North);
    theList1.push_back(GBR_National_League_South);
    theList2.push_back(GBR_Northern_Premier);
    theList1.push_back(GBR_Professional_Development_League);
    theList2.push_back(GBR_SPFL_Development_League);
    theList1.push_back(GBR_SPFL_Development_League_2);
    theList2.push_back(GBR_Scottish_Challenge_Cup);
    theList1.push_back(GBR_Scottish_Championship);
    theList2.push_back(GBR_Scottish_Cup);
    theList1.push_back(GBR_Scottish_League_One);
    theList2.push_back(GBR_Scottish_League_Two);
    theList1.push_back(GBR_Scottish_Premiership);
    theList2.push_back(GBR_Scottish_SWFL_Women);
    theList1.push_back(GBR_Scottish_Womens_Premier_League);
    theList2.push_back(GBR_Specials);
    theList1.push_back(GBR_The_Championship);
    theList2.push_back(GBR_Welsh_League_Cup);
    theList1.push_back(GBR_Welsh_Premier_League);
    theList2.push_back(GBR_Womens_Super_League);
    theList1.push_back(GEO_Georgian_Division_1);
    theList2.push_back(GEO_Pirveli_Liga);
    theList1.push_back(GIB_Gibraltar_Premier_Division);
    theList2.push_back(GRC_Greek_Division_2);
    theList1.push_back(GRC_Greek_Football_League);
    theList2.push_back(GRC_Greek_Super_League);
    theList1.push_back(GRC_Greek_U20_Super_League);
    theList2.push_back(GTM_Guatemalan_Liga_Nacional);
    theList1.push_back(GTM_Guatemalan_Primera_Division_de_Ascenso);
    theList2.push_back(HKG_Hong_Kong_Division_1);
    theList1.push_back(HND_Liga_Nacional);
    theList2.push_back(HRV_Croatian_3_HNL);
    theList1.push_back(HRV_Croatian_Division_1);
    theList2.push_back(HRV_Croatian_Division_2);
    theList1.push_back(HRV_Croatian_U19_League);
    theList2.push_back(HUN_Hungarian_Cup);
    theList1.push_back(HUN_Hungarian_NB_I);
    theList2.push_back(HUN_Hungarian_NB_II);
    theList1.push_back(HUN_Hungarian_NB_I_W);
    theList2.push_back(HUN_Hungarian_U19_Division_1);
    theList1.push_back(IDN_Indonesian_Cup);
    theList2.push_back(IDN_Presidents_Cup);
    theList1.push_back(IND_Calcutta_Premier_Division);
    theList2.push_back(IND_Delhi_Senior_Division);
    theList1.push_back(IND_Goa_Professional_League);
    theList2.push_back(IND_Indian_Super_League);
    theList1.push_back(IND_Mumbai_Elite_Division_League);
    theList2.push_back(IRL_Airtricity_First_Division);
    theList1.push_back(IRL_Airtricity_Premier_Division);
    theList2.push_back(IRL_EA_Sports_Cup);
    theList1.push_back(IRL_FAI_Cup);
    theList2.push_back(ISL_Icelandic_1st_Division_W);
    theList1.push_back(ISL_Icelandic_Cup);
    theList2.push_back(ISL_Icelandic_Cup_W);
    theList1.push_back(ISL_Icelandic_First_Division);
    theList2.push_back(ISL_Icelandic_Fourth_Division);
    theList1.push_back(ISL_Icelandic_Premier_League_W);
    theList2.push_back(ISL_Icelandic_Second_Division);
    theList1.push_back(ISL_Icelandic_Third_Division);
    theList2.push_back(ISL_Icelandic_U19_League);
    theList1.push_back(ISL_Icelandic_U19_League_Women);
    theList2.push_back(ISL_Urvalsdeild);
    theList1.push_back(ISR_Israeli_Liga_Alef);
    theList2.push_back(ISR_Israeli_Liga_Leumit);
    theList1.push_back(ISR_Israeli_Liga_Leumit_Cup);
    theList2.push_back(ISR_Israeli_Premier);
    theList1.push_back(ISR_Israeli_Premier_League_Cup);
    theList2.push_back(ISR_Israeli_Super_Cup);
    theList1.push_back(ISR_Israeli_U19_Elite_Division);
    theList2.push_back(ITA_Campeonato_Primavera);
    theList1.push_back(ITA_Coppa_Italia);
    theList2.push_back(ITA_Coppa_Italia_Lega_Pro);
    theList1.push_back(ITA_Lega_Pro);
    theList2.push_back(ITA_Serie_A);
    theList1.push_back(ITA_Serie_B);
    theList2.push_back(International_AFC_Champions_League);
    theList1.push_back(International_AFC_Cup);
    theList2.push_back(International_CAF_African_Cup_of_Nations);
    theList1.push_back(International_CAF_Champions_League);
    theList2.push_back(International_CAF_Confederations_Cup);
    theList1.push_back(International_CONCACAF_Champions_League);
    theList2.push_back(International_Copa_Sudamericana);
    theList1.push_back(International_Euro_2016);
    theList2.push_back(International_FIFA_World_Cup_2018);
    theList1.push_back(International_Friendly);
    theList2.push_back(International_International_Friendly);
    theList1.push_back(International_International_Friendly_W);
    theList2.push_back(International_U19_Internationals);
    theList1.push_back(International_U20_International);
    theList2.push_back(International_U21_Euro_Championships_Qualifiers);
    theList1.push_back(International_U21_International);
    theList2.push_back(International_UEFA_Champions_League);
    theList1.push_back(International_UEFA_Europa_League);
    theList2.push_back(International_UEFA_Youth_League);
    theList1.push_back(JAM_Jamaican_Premier_League);
    theList2.push_back(JOR_Jordan_Cup);
    theList1.push_back(JOR_Jordan_League);
    theList2.push_back(JPN_Emperors_Cup);
    theList1.push_back(JPN_J2_League);
    theList2.push_back(JPN_J3_League);
    theList1.push_back(JPN_J_League);
    theList2.push_back(JPN_Japan_Football_League);
    theList1.push_back(JPN_Japanese_League_W);
    theList2.push_back(JPN_Nabisco_Cup);
    theList1.push_back(KAZ_Kazakhstani_1_Division);
    theList2.push_back(KAZ_Kazakhstani_Premier_League);
    theList1.push_back(KEN_Kenyan_Premier_League);
    theList2.push_back(KOR_K_League);
    theList1.push_back(LTU_Lithuanian_1_Lyga);
    theList2.push_back(LTU_Lithuanian_A_Lyga);
    theList1.push_back(LTU_Lithuanian_Cup);
    theList2.push_back(LUX_Luxembourg_National_Division);
    theList1.push_back(LVA_Latvian_1_Liga);
    theList2.push_back(LVA_Latvian_Reserve_League);
    theList1.push_back(LVA_Latvian_Second_League);
    theList2.push_back(LVA_Virsliga);
    theList1.push_back(MAR_Moroccan_Cup);
    theList2.push_back(MAR_Moroccan_Division_1);
    theList1.push_back(MEX_Copa_Mexico);
    theList2.push_back(MEX_Mexican_Liga_de_Ascenso);
    theList1.push_back(MEX_Mexican_Primera_Division);
    theList2.push_back(MEX_Mexican_U20_League);
    theList1.push_back(MKD_Macedonian_Football_League);
    theList2.push_back(MLS);
    theList1.push_back(MLT_Maltese_First_Division);
    theList2.push_back(MLT_Maltese_Premier_League);
    theList1.push_back(MMR_Myanmar_National_League);
    theList2.push_back(MYS_Malaysia_Cup);
    theList1.push_back(MYS_Malaysian_Super_League);
    theList2.push_back(NIC_Nicaraguan_Primera_Division);
    theList1.push_back(NIFL_Premiership);
    theList2.push_back(NLD_Dutch_Jong_Eredivisie);
    theList1.push_back(NLD_Dutch_Jupiler_League);
    theList2.push_back(NLD_Eredivisie);
    theList1.push_back(NLD_Eredivisie_W);
    theList2.push_back(NLD_Netherlands_Reserve_League);
    theList1.push_back(NOR_Norwegian_1_Division);
    theList2.push_back(NOR_Norwegian_2_Division);
    theList1.push_back(NOR_Norwegian_3_Division);
    theList2.push_back(NOR_Norwegian_Cup);
    theList1.push_back(NOR_Norwegian_League_W);
    theList2.push_back(NOR_Tippeligaen);
    theList1.push_back(PAN_Panama_Primera_Division);
    theList2.push_back(PER_Peru_Primera_Division);
    theList1.push_back(PHL_Philippines_UFL_Cup);
    theList2.push_back(PHL_UFL_Division);
    theList1.push_back(POL_Ekstraklasa);
    theList2.push_back(POL_Ekstraliga_W);
    theList1.push_back(POL_Polish_1_Liga);
    theList2.push_back(POL_Polish_2_Liga);
    theList1.push_back(POL_Polish_Cup);
    theList2.push_back(POL_Polish_U19_Central_Junior_League);
    theList1.push_back(PRT_Campeonato_Nacional_Seniores);
    theList2.push_back(PRT_Portugese_Super_Cup_Women);
    theList1.push_back(PRT_Portuguese_U19_Championship);
    theList2.push_back(PRT_Primeira_Liga);
    theList1.push_back(PRT_Segunda_Liga);
    theList2.push_back(PRT_Taca_da_Liga);
    theList1.push_back(PRT_Taca_de_Portugal);
    theList2.push_back(PRY_Paraguayan_Primera);
    theList1.push_back(QAT_Qatari_Stars_League);
    theList2.push_back(ROU_Liga_1);
    theList1.push_back(ROU_Romanian_Cup);
    theList2.push_back(ROU_Romanian_Liga_II);
    theList1.push_back(ROU_Romanian_Liga_III);
    theList2.push_back(RUS_Premier_Division);
    theList1.push_back(RUS_Russian_Cup);
    theList2.push_back(RUS_Russian_Division_1);
    theList1.push_back(RUS_Russian_Division_2);
    theList2.push_back(RUS_Russian_Regional_Leagues);
    theList1.push_back(RUS_Russian_Youth_League);
    theList2.push_back(SAU_Saudi_Crown_Prince_Cup);
    theList1.push_back(SAU_Saudi_Premier);
    theList2.push_back(SGP_Singapore_Cup);
    theList1.push_back(SGP_Singapore_Prime_League);
    theList2.push_back(SGP_Singapore_S_League);
    theList1.push_back(SLV_El_Salvadoran_Primera_Division);
    theList2.push_back(SRB_Serbian_Super_Liga);
    theList1.push_back(SVK_1_Liga_East);
    theList2.push_back(SVK_1_Liga_West);
    theList1.push_back(SVK_Slovakian_1_Liga);
    theList2.push_back(SVK_Slovakian_Cup);
    theList1.push_back(SVK_Slovakian_Super_Liga);
    theList2.push_back(SVK_Slovakian_U19_League);
    theList1.push_back(SVN_2_SNL);
    theList2.push_back(SVN_Slovenian_Prva_Liga);
    theList1.push_back(SWE_Allsvenskan);
    theList2.push_back(SWE_Superettan);
    theList1.push_back(SWE_Swedish_Cup);
    theList2.push_back(SWE_Swedish_Div_1_Norra);
    theList1.push_back(SWE_Swedish_Div_1_Sodra);
    theList2.push_back(SWE_Swedish_Division_1_W);
    theList1.push_back(SWE_Swedish_Division_2);
    theList2.push_back(THA_Thailand_Division_1);
    theList1.push_back(THA_Thailand_Division_2);
    theList2.push_back(THA_Thailand_FA_Cup);
    theList1.push_back(THA_Thailand_League_Cup);
    theList2.push_back(THA_Thailand_Premier_League);
    theList1.push_back(TUN_Tunisian_Cup);
    theList2.push_back(TUN_Tunisian_Ligue_Professionelle_1);
    theList1.push_back(TUR_Turkish_Division_1);
    theList2.push_back(TUR_Turkish_Super_League);
    theList1.push_back(UEFA_Champions_League);
    theList2.push_back(UEFA_Europa_League);
    theList1.push_back(UKR_Ukrainian_Cup);
    theList2.push_back(UKR_Ukrainian_Druha_Liga);
    theList1.push_back(UKR_Ukrainian_League_W);
    theList2.push_back(UKR_Ukrainian_Persha_Liga);
    theList1.push_back(UKR_Ukrainian_U19_League);
    theList2.push_back(UKR_Ukrainian_U21_League);
    theList1.push_back(UKR_Vischya_Liga);
    theList2.push_back(URY_Uruguayan_Primera);
    theList1.push_back(URY_Uruguayan_Segunda_Division);
    theList2.push_back(USA_MLS);
    theList1.push_back(USA_NPSL);
    theList2.push_back(USA_North_American_Soccer_League);
    theList1.push_back(USA_USL_Pro);
    theList2.push_back(USA_US_Open_Cup);
    theList1.push_back(USA_US_PDL);
    theList2.push_back(USL_Pro);
    theList1.push_back(UZB_Uzbekistan_1_Division);
    theList2.push_back(UZB_Uzbekistan_Cup);
    theList1.push_back(UZB_Uzbekistan_Professional_League);
    theList2.push_back(UZB_Uzbekistan_Youth_League_U23);
    theList1.push_back(VEN_Copa_Venezuela);
    theList2.push_back(VEN_Liga_de_Ascenso);
    theList1.push_back(VEN_Venezuelan_Primera);
    theList2.push_back(VNM_National_Cup);
    theList1.push_back(VNM_VLeague_1);
    theList2.push_back(VNM_VLeague_2);
    theList1.push_back(ZAF_8_Cup);
    theList2.push_back(ZAF_Premier_Soccer_League);
    theList1.push_back(ZAF_South_African_First_Division);
    theList2.push_back(ZAF_South_African_League_Cup);
    theList1.push_back(ZAF_South_African_Varsity_Football_Challenge);
    if (side == 0) {
      return theList1;
    }
;    return theList2;
  }
};

#endif // BfCompetition_H
