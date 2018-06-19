#include <algorithm>
#include <fstream>
#include <memory>
#include <array>
#include "google-generated/route.pb.h"

// generate a pbf file based on the request:
//    'https://api.mapbox.com/directions/v5/mapbox/driving-traffic/-77.03400313854218,38.899923675122196;-73.99072587490082,40.756567079102425?access_token=pk.eyJ1IjoiaGFwcHlnbyIsImEiOiJjamF2YjR3M3M3MHZvMzNuaXczZmlkem95In0.1HHBIuWNJsipt4g8VDQlMw&geometries=polyline6&steps=true'
int main() {
    using namespace valhalla;

    // bounding box
    BoundingBox bb;
    bb.set_max_lon(-73.9434814453125);
    bb.set_min_lon(-77.1624755859375);
    bb.set_min_lat(38.83542884007305);
    bb.set_max_lat(40.81796653313175);

    // route
    Route rut;
    rut.set_duration(14054);
    rut.set_distance(369.377);
    rut.set_allocated_bounding_box(new BoundingBox(bb));
    Leg* leg1 = rut.add_legs();

    // directions response
    Directions miz;
    miz.set_uuid(500);
    miz.set_status_message("Found route");
    miz.set_status_code(0);
    miz.set_units("miles");
    miz.set_language_code("en-US");
    miz.set_allocated_bounding_box(new BoundingBox(bb));

    // leg
    leg1->set_summary("DC to NY");
    leg1->set_distance(369.377);
    leg1->set_duration(14054);
    leg1->set_allocated_bounding_box(new BoundingBox(bb));
    leg1->set_geometry("}}geiAh`x|qC?iM?qGlE?hC?v|@\nCOdE?pC?vHNvS?|D?`m@]pG?rF?dj@_@`G?jFMld@_@xH?z@?`Hl@`C?jQN~W\u000bN?znAMfY?vWOzGNtJj@dT?pMNxAOlF]tDm@hH{AxB{@jB}@jFwCpBkAxL}IhCkBnCiBhCkA|DkBrBm@vC{@`HkBnDm@zE]jBMzEObBNpB?xBLfDNxMxBvCl@nCl@fDxAxBlArFtDhCxB~CvCbGrGbFdEhCzAbBz@xBl@~B|@lE\\zG?tD?|i@NxLLxLMbLOdmA?hH?lJl@zF\\|DOjBMlE{AxBwDvM_SzKkVjBuExLsZfI_TzAwCpBwDfXum@nDcQhC{KbPm~@dAaHjAaHjAqG|@sFxAkLlAa]?qGGqG_@qHUcFe@aHe@cGm@qGm@aHcAePWcGMaHGqG?aH?qGF}^?kA?qH?cG?oHGcGFaH?cG?oH?cGFaH?qH?sFLaQFuF?cFt@wb@d@sPeA{|CUsdAF}^]{t@DeZEmnELor@FaRTwNl@gNt@wNt@{JjAgNxBqRjA_JrA}Iz_A}bFhByLvCgYVgDl@oHLyCV_ILwCdA{_Ar@_gAt@_^NcFr@iMNiB|@oId@yC\\gDnDiVrAaI`GuYpRgbArFwXzVguA|D}TdJqg@lUw`BzKyv@~Hgm@hWooBrA}JrAmJlEeZfDwN`CqGjKoSrGqGdEgDhGuE~IwCtJkB~M]dJNzLz@r~@tE~b@jAhHNvSLpGm@xG{@jF}@zGyAnHkB|E{AzKsE~HgEpLoHnDiCtJoH`RiN|ZsPxu@uc@lEgDbFuEbBiBnCuEhCsFxBeFzAuEnDgNvCuOpBwNdA{KLuDd@qRNmJ]qRm@iM}@iLgCqRiCiMgNcf@se@o{Ayg@k~AwM}]uO{`@uY}s@u_@iaA}IkU{La\\uIkWuKq\\cFqQ}Yk_A{F_TiG_TmKk_@oHs[_E_T{E_^yCeZaBwXyC{s@_Cah@sAqQkBcQsAkL{@qGgDsQeEaQ{G}TyFeP_JqR{KoSiMqRqRiWoSkVsi@{j@sf@wb@k[kVaa@eYiWuOkQ}JeP_Iwg@{Us[{Lmn@oSafAq[cu@oT_fAs[ud@uNkLgE{EyB}EgC}EyC{EwCuEgDuEgDmEeEuEuDeEuEeEuEeEcFwDuF}DsFoDaG_bAgkBaHgNcVud@sKoSwMmUeKuOqG_I{LkLyQuOqWoRi_B{~AoCiCqHoHqBkBsj@{i@uTiXiSuY_IiLeOoTgDuEeFqGyBiCyLgNqGaHmKiLaRoSoDwDaGqG_^m_@iHqHeUiVav@ceAk`@mi@ib@un@q[uc@a]ud@uY}^{u@{_AeEsFyWc[e_@ce@oXs[kUwX{o@cz@eUc[mP}TeTwYyMeO}SmTmZ{UeJqHcLmJo^c[aMmKk`@q\\shBk}AuN{LcByAqBkBkLmJoDwCkKoIcFuEgNyLc\\gXwCiC{PeOoYkV{FuEiV_TiSaRuOkLyLoHwHwDgIeEuPaH}OcFi[mJ{KyBgO{BmJ{@cLOsP]wN?st@wCcu@gD_r@kAmd@kA_x@iCsV}@wSm@yQ{@yR}@}SeDuJkBoIwCcQsGqL_H}O{Koc@eZm}@or@gOmKmOmJ{UuO_r@ud@s`@wWcR{L_zBsxAy\\kUsKaIuJmIaMmKeOePgOcPgNcQuJgNsPyWiMmUoNuYqLwXsLq\\uIwXoO{j@uc@k~AsP_g@gJ}UoRia@aNiWkPyW_OoSeP_S{@kAqLiN_ZwXgN{K}Y}SiWyMoXyLwh@}TsUkKkPaIwIsEmUgNcP{KmPkLkQuO{OuOePsQoXsZiXc[{KkLi\\o^yQaRoNiM}OgNsPwMaXsQkUwMeU}JyRqHeUoHyQuEqWsFeUgD_XwCgTkA}X}@mU?mU\\e{B`HmY^uUOsP]}T}@mP{AaRiBiRwC_SwDePuD_SuFyRaGcQaHoNcG}NaHqRkKeUgNgSgNcoAa|@_OmJsP{KgN_IqQmJuU{K{UoIiMwDiMuDqRuEuNiCoNiBiRyBaX{A_}@wC{Pm@wb@kBwSkAgSiBsQiCqL{AyLyBoJiBuIyB{PwDoNeE{U_IyW}JsV{K{UiMsUwMwSyMg|A}gAqWcQiWsPe_@oTm_@_Sq\\sPob@qRib@sPw\\iN_^uO}YcPgTyLg]}Tq\\{VwX{UcVmTeU}UgSoSya@gb@a]q\\eUoSqVqRkWsQa\\}SgXgOa]sPsVkK{U_JmZ}J_XoH{Z_ImlCcq@}X_IqWoHuZ}Jqa@yMkj@}SeZkLgXyLy\\ePw]_SoYcQ}OmKkUsPgSuOqRuO{QePuYgX_SoSiS_Tce@mi@wCuDePoSwNaSuDuEca@yk@iV_^cRuY}OyWgNgXkK_TeOa\\aMa]wIkViH}SgIkV{Kwb@kKwc@cLkj@qMcp@ck@e`D{Oq{@yH}^eJya@aMqf@yMaf@eOcf@eKuZ}Ngb@uOk`@sLuY_Sib@sKmTsL}T}T{`@iVk`@cRyWgSgXeTiW}UkVmToSgX}TgTgOsFeEc[qRm_@aRgh@{Uy\\wMe_@iN}Y{KaeAa\\{`@kKkVcGko@wNy~Bqf@iuEy`AqmCik@eiAiXob@kKal@uO{iAc\\ck@aQmd@wNmi@cQus@{Ums@kV}mAib@{mAgc@cdBen@gfAia@cV_Jgx@sZoS_IsPsGmOaGgrAoh@ip@yWsVmJ{e@_T{j@{Uaq@uYiu@c\\ir@c[kiA}h@olAkk@sj@gXak@gYikAwl@yv@ia@qf@iWcf@gYecA}i@}uBwkA{t@k`@kf@{Uqp@s[en@wXig@mTgSsGecAy`@iw@eZes@iXaMsE{o@kWaRoHuU_J{lB{t@sVmJwg@qRkeAya@al@iVse@qSex@m^qv@{_@cf@{VioA_s@_r@wa@yq@ib@ob@gYos@af@sd@q\\gs@_h@so@se@wg@k`@ag@{`@en@ag@cq@kk@oq@gl@yp@gm@iq@eo@ku@kt@st@ku@_n@or@oXq\\i]gc@aa@{j@c`@ik@u_@il@md@or@{d@_s@md@or@}_@il@ed@or@s`@wl@c`@kk@{e@aq@af@ap@ab@}i@ud@kk@se@ik@}h@gm@gh@yk@qg@_i@gg@oh@ck@yk@cj@kj@eo@so@{_@k`@wTmUmd@ce@}c@qf@k[q]wWeZ}UeY{UuZsj@or@ed@yk@cVuYql@ux@oNoSq[ud@sf@mt@qVk`@gYed@u_@un@mc@{s@qg@uy@{d@iv@sk@y_Aso@gbAom@o|@q\\ud@wRiXaSiWqk@kt@__Ds_Een@yv@q\\ed@g^qg@_^og@qW{`@sZse@mgBk{CkKaRyyB{{Dm_@so@gc@or@or@qeAi[uc@}_@oh@kUeZqWa]{`@af@_r@iw@e`@gb@}r@ms@q{@ey@o}@yv@ky@cp@yyBk~Acp@wb@ap@y`@c{@qg@cj@c[mj@eZct@m_@et@_^oh@yV{sAwm@}w@q\\snAag@ui@_S{sAcf@}OaGePsFmOuFi~Gg_CwuF_pBsPqG{PaHwTmK_XwMiWgN{VgOq\\mTqW_Se_@eZqV}T}^o^gIoI_zCkfD_{AebBoiD_wD_kG_`Hsj@il@e_@y`@kj@mj@eZeYs`@o^{e@gb@ojBi`BoXkVeEgDiSqQqGcG}EeEoHcGabE}nDgSsP{mFqvEipEi{DsgCozB{iFwrE}DgDydBqzAujDmyCct@eo@}YwXcWgX{Z_^q\\ib@iRyWcV}^eUm_@eTk`@gSia@ePm^kQib@eOia@iMo^sKo]}J_^}n@i~BoaAuiDa]coA}Owm@kPwl@{_@snAsGePqRgc@{OsZuOyWiMqRiMcQqMePwNcPeOuOmTaSuUqQol@gc@cMkKaMkLmT}TyRmUqQ{TaSwYilDugFeZuc@a\\cf@eZse@gX_h@aSib@cQec@}IkV_Nya@oN_h@uJm_@uxAycGgC{Kui@sxB}lBo~HmbAc`EoSo{@c\\_rAwr@euCyFmUoJ{_@kFuPoIeYgIkV_I{U}ImUaMuY{LgXkKoS_JcQiGiMg]oh@qSgYaRiV}SkVgTmU{ZeZeU}ScVaS{VsP_XgNwX{KyRcG_SeEyLyBoSkB_TiBaiCoSa{@qGom@uEe_@_J}D{@gDkB_EgDmDuDqCwDoCqGcBcFsAaHu@qHMaHLcGd@_IpRcwBxHglAnIwx@lDo]nTewBtDk`@nSqnBnNk~AnSisB~Do^rUswBnc@yfErF}h@|Dud@hBed@?{_@yAil@qC{`@cF{`@kFa\\oIq\\mEyMoDwMaRya@sK}TgOkVeOqRmOaQiM{KmPwO}OyLq\\kVo]gX}eHcsFwScQoNyMuNuOaNcQ_NaQyLqSsLmT_NeYeK{VaMo]sJo^aDwNgCiLeFwX{Ec[oDs[iCeZeEqq@uEms@qG}gAsAoSeK}fByA{VgD}i@qBce@cBuc@sAud@]kV_@ePe@{j@cAkeDoC{uIu@umAOse@Gqp@s@w_Cr@sy@?oIyAytAOeFkA{rBW{iAFgb@{@wb@yBmi@sFcf@gEgXqGwYiHkVaLwX{K{TwNsQiMuOgNwNkQiMwDgCwM_Jca@gXyk@uZ{sAww@y~Aex@kqZmkQuy@kt@mJmKyR}TwM_S_Ygc@wIgNcQuYip@sdAyGmJsV}^eTeZc\\k`@ow@a|@{t@sy@mn@os@om@aq@oc@af@q_Ao}@wYkUeZiW}r@wc@}ZeOgX{KyQcGqMgDeE{@yLyB{F}@}E]}Dm@sF]}EOcF]uEOyL?eFOgSNoSNmZLaMN{KNuE?gXLcVNknAjA_^?yW?}OOcLNm^jA_T\\sZ^_Z\\u^z@qQ^uUl@eZz@sF?sZ|@s`@jAu_@z@o]|@iq@zA}^xAmo@jBmNL}U^kZjAiWl@eZz@o^l@kV?uOkAcLm@uD]yHkAsJkAeKiCgDm@oXmJkGyBiWiMcUyMqWaQui@ka@{[}TiByAkQ{LiRgNya@s[_m@y`@yf@q]_n@ia@{n@uc@aXoSwSiNmTsP_c@s[sk@{_@iWsPm}@un@gc@c[ud@e[}XoRqR{LmEgCmEyCeFgCwCkB{@]mEiCom@a\\{o@s[o^cQeOaHud@mTed@mTqRmJqQoIud@}T}~@wc@g|@_^}c@wWe~@so@ca@}_@c_Am~@_fA}gAa]a]uzCk{Cu}@}}@oh@kk@}jCyrCw}De~DwkBulBgmDmnD{bCqcCqV{V__@o]e_@s[ce@o^{`@eYwg@s[af@gXig@yWunEqoBuYgMmYePaXsQeZyVkU{UsVwXaW}^_To^eOc[gOo^}{B{wFuc@kjAidBifE_vBouFakAqxCooCeoHmaBmyDqk@oqAgbAqcCucAiiCg^_|@g]wx@a]_r@y[gm@sVwb@{dAkhBi\\wm@eYik@eZeo@w]ux@klHkwQazAqvDgn@_{A{_@a|@kKoSePc[qHePwN{U{OiW}d@un@gX}^_h@eo@qkAqzAewAk}AadCwjCq}CcaDeqBguBq{@{~@m|FcsGmzCocD{e@ed@c`@m_@{`@}^ia@o]_{FyzE_d@k`@{T}ToYc[oSmUaXa]wW}^{V}^wwRupYuTuZyQmUiSkUmTmTcVoTgSsPsQiMyQkL_YaQ_oCczAcp@}^a\\cQcVcPgTePkQuOiQsQaMgNwNqQ_O_ToM_T_OwWmOc\\qMa\\gNya@yMib@epCqeJ}Nce@mPcf@aR}h@gSmi@gTmi@qRgd@eYap@gYyl@qVqf@iXqg@wXqf@e_@co@{Zcf@ytOodVcLqQ}JgOavDs}FeZaf@mPuZuOa\\qQya@{Pcf@_Ose@iMag@oI{_@aH{_@aHgd@aG_g@oD{`@gDmi@qBag@u@ib@U_h@rAgbIlEaxV?gc@m@_h@}@o]sAo^aBuYyCo^mEgb@sEm_@iHed@qHm_@kKce@_Jo]uzGsaV_Oqg@sPmi@yMia@aR}i@{Pse@}Oia@oRse@cV{j@kk@apAa\\_s@yoBolEcLyVg|@qoBil@}qAgh@gmAed@kiA_Y{t@{s@ooByg@qzA}Yq|@s`@ulAqf@_|AeZi`Ak[ceAg]emAuUcz@yrGkgUopBycHiRso@iRyk@oSwl@qk@}}AyRag@uT}h@_Tud@wSy`@gSo^aWya@cW}^}Yia@s_@ud@udDetDmUgYiRyVaMaRyLqR{LoTmJqQ_IePyLwWoIqS}IiVonD_rJ}JwX}h@exAc`@ofAyMia@kLm`@cKk_@mKgc@oHo]wIud@uqAkvHuJqf@gJka@eJy`@cLwc@yLya@eOaf@{Lo^oMo^oNm^oOo^sUog@kVqf@iR_^_Sa]uT_^aXy`@q\\gd@a\\ia@m_@gc@i\\q\\c\\s[_r@so@yR}SmTwYgN}SyLoT{cFgjKoTka@kPgXqRgXsUgYuUmUoSoRoXqRwaAsp@{UaR}PcQ}NsPiMsQiMoS{K}SgIcRmJiWeJeZgJ}]g]wvAkjAkzE{Kwb@aLya@iM{`@eKc[wN{_@eO}^eTse@ePs[yRo]oSa]}O{UeTeZ{UeZqXc[arUu_WqWeYwsHagIqMgOmOqR}O{UwN{UyL{U}JoSuJ{U{Kc\\izFixQqL_]{KiXsPia@gTud@qV_g@cVya@yWyb@_Yia@yVq\\qXa\\a\\o^cf@ce@w]uYs`@uZia@gYal@_]cj@wYu|F{zC}_@oSiVgOq\\}Tk[{UgY}ToXiWoXyWwT{Ui\\{_@gNcQkVs[yoEw{Fg}E{lGm^qf@w]qf@_^oh@yl@{~@{aL{lQc[uc@_TwXwXc\\eZa\\sZeZu_@a]akAy`AupC{|BepCk}BwWkUwSaSwSkUwS{ViRiV{Uq]mPwWcQeZkUud@oTse@qLeZyM}^sJuZoNaf@cLwc@eKse@sKum@qHsf@kFed@uEsd@_Ded@oCoh@cBka@s@og@eAafAmJs`M]}_@u@q\\{AwXaC{UoCyV_DqReEoTsFiVaHkWaIiVyLyWmn@gkBor@}pBcwBmlGmyEabNkP_g@uJ_^gI{`@mEa\\aCgYiBgYeAeZ]uYOeZd@itB`DokOGyWGc[e@sZ}@}TcAoS}@mUeDgc@aDq[_DiX}DeY}DiWkGs\\iGsZuJwb@iXwbAmEcPkFaRqGcRcLwX_OcZ{PeZog@iw@kAyAu@mAgN}SmPkV_^se@yk@iv@}N_SiRgYq{@mrAy\\qf@k~AeaCaRuZkQq\\qLyW{LsZmI{VoJc[mI_]qHo^iHya@gD}Tko@w}DyrCsfQmJ}i@_Jce@oI{_@sKed@gIeZmJa]}Oag@wM}^oNm_@kQwb@kqCq~GaMq[gOib@_IkVyG}TsLwb@yLaf@sKag@iHq]oIqf@qGya@cFia@aHkk@iiCalVk}AqaOaHgm@{Fed@yGgb@iH}_@iHa\\}Io]_JuZmJeZgN}^gNq\\_OsZoNiXwNyWeOiVkeE_vGagI_nMcKcPcuAsxBaMmT{OgYwNwXeKoSwMeZ}JkUgN_^cLc[eJgYsLk`@yLwb@uJ}_@wI}^oHm_@oIsd@qGya@mF}^kFwc@}Dya@eEag@yCwb@_Ccf@yb@sbKeOwiDyBse@yBm^aCa]oDia@mEia@cFka@kGwb@sFo]iGo]yH}_@uIm_@uJia@uJo]eP_i@wSgm@_N_]yWeo@uTag@gaK{qUs`@}}@iWil@}{BsiFsUyj@iRag@yVqq@aSyk@}IyWi|@qmCqf@o{AoNee@iMuc@yLse@mJk`@uJwc@cLyk@wIag@kxA}rI_Ioh@oDs[aCyWyBa\\kAsZu@gYUwXFa\\l@eZz@eZbBc[xBgYfCiWpC_SfDkVzEiXlEoS`I_]fxD}cOvHq\rFwX|EeZtDiWxCwXfCwXpBq[lAe[r@_]NuYGuZm@sZu@{VyAuYsBgYwCs[{qBszRom@kbGgD{`@qCk_@aCib@aBq\\kAwb@u@q\\m@s[Oo]Es[Ta\\d@{`@t@a]rAk`@`B{_@rBa]~Bo]`Dm_@lDo^tE{_@rFya@xGed@hH{`@xGq[nTecAlJwc@fHm_@jG_^pGsd@xHgm@zF{j@lDse@fDag@hCmi@hBqg@dA}h@\\ed@F_h@W_^]}^}@ka@aBse@qC_h@gDag@mDuc@eFoh@aGqf@iHcf@enEajXqH_i@{E{_@mFcf@sEyk@iCk`@iBk`@cBce@sAed@e@ib@Ouc@Fud@d@wc@|@gc@jAgb@hBya@xCqf@tDcf@dEed@dFud@pGqf@xGwb@zKwm@v|@qkEro@qbDhHy`@~Hsf@zFec@|Eib@tEag@dE}h@vCsf@pBse@zAaf@t@ce@`BoqA^ya@zPwzPt@wb@bA_h@bAwb@pBim@`Cmi@`Cmh@fD{j@lEun@|Eeo@rFen@`f@q_FpHku@nb@ifElEed@hCwX|Ecf@~q@ybHtDka@`CeYhCm_@bBm^rAm`@r@q[l@_^NeZ?ia@O{KM{V}@gb@kAya@sAc\\qB_]_Dgc@gD}^gE}_@eEo]{Es[cGm_@qGq\\ar@w~C}S_|@qX}hAmn@moC{j@wjCqf@sbCmi@amCcVwvAob@evB_@{Ae@{AoM{j@sQso@iWk_AgXmrAoIor@gDen@wCa]sAuc@qC_}@e@a|@OyiKUquE{@a`Fg@}_@kAc[oHmgA_Ese@cK{_AoDa\\ig@qlEgDsZi\\_oCyG_i@wXcwBeOsoAkVwjBqa@_nDeE{_@gEo^oM{hAsFcf@_Eq\\aHyk@yeAm~Igc@irD_Hik@cq@mwF}TsyA{UyjAse@wjBqz@y}B_wAwjCs[un@mTwb@wr@gaBww@ozBse@ksAqp@_qAwc@sp@ya@{i@cVkWal@}h@{lBofBiMgMeU{V}J}I}DgDsQiWmTa]aMmU}c@sy@mi@ktAkiAqwCemBgrEgXse@m@kAcLoSgDsFolE}vFud@gn@so@sy@qjA_|AePkVcA{Ak_Ai_B{u@qyAol@apAig@ikA{i@_fB}Ose@eU{t@s`@gvAiMqg@mOco@cQww@wMqq@mKmi@cQgaAwNwx@cPsy@sKoh@oNcp@eUw`AmPeo@qGyVeUy`AeZgvAcVmiAk[qyA{Kag@_h@acC_Iq\\gm@gjCurAgfG}sD}_QgSk_AgDsQcu@skD_i@kgCqf@y}Bmn@gtCeO}s@eVwvAum@awDk[}pBeZy}Bu^kfDu_@uiEmEyk@eEey@oN_dCkBib@cAmi@]_r@]_}@rAag@|Doh@hH}h@tJoh@|Nwl@|Oud@fN_^lPuZj_@}r@bMqRpjA{gBdd@ku@vSwb@|Ymt@fN{_@`]sdAdTiv@lKwc@lEa\\~BiWdAcf@Guc@iC_i@_DsZoIgc@_Sor@cLqf@}Iaq@qCc[qB{`@?k`@`C_{Bz@coAl@aq@|EmnDjAecAjAgbA`CayBvC_qBxBguA~D{}BT_Tl@uYpBubAt@{UnDsoAnHqaErAm}@pB{iAhHc`EbBq{@rAeZnHy_AzFmt@rAsPbLy`ArKor@nNux@psP}cs@h`AakEpfAyzE|m@kgC|d@_pBhW_hA`\\mfBbWyuAdE}Tl^opBvDiVfIgn@|Io|@pCo]hCka@rA_]d@yLhBun@xBcoAFaRN_JOeO]}^W_^yB{_AsA{`@{AsZwCoh@iC}^{JwaAwSi`Bql@qsFeEe[mEgb@qG}i@}Eoh@eEec@_NmiAsG}h@gNksAuh@stEuUytB]wCeZclCikAyiKkKww@_D__@gD_g@mE{u@cAqp@sAcf@qCen@gDib@aGce@sBwNmDs[uJ}r@{FwXoIq\\}EaSsFiWwHc[cGkj@{Eqf@eF}i@gDmUwCse@yl@q}G_vAinPwMy_BaXk|Co^ehEeJwbAwHkt@{Fcf@aHkj@aH_h@yRapAsFs[iLso@wN{t@eKse@oeBkkIgNso@g}@eiEco@{{CyMen@qk@_oCyoBgmJ{U{hAmqBoqJk[_|A_Sk_AkVmhAoNwm@_YijAw_CucJgIa\\aH{V{Kuc@shBgdHapE{bQ_c@adBag@cmBa]umAaLm_@_n@wjBwN_^oM}_@kQog@eKgYwM{`@mPse@eYa{@m_@qeAcQce@mYey@qv@cxBgYsz@a\\k_AcLsZmx@{}Bwr@krBsGoSmgAeuCka@mhAob@glAyf@wvAwl@scBqb@wkAwg@uwAiRag@aSoh@}ImT{Pk`@wg@}gA_~@{hBaM{Uyp@_rAqRm^mqBg}Daq@aqAc_E_~Hqq@qoAwvAkrCoaAaoBk_AyhBesAkgCia@uy@eZwl@{Uqg@yRm^_Yoh@oaEm_IurB{zDmJqQuh@mhAgoCknFiq@glA}Tib@_Ted@u^ms@iRya@}Tud@wX_h@{FkLsUce@al@_gAqg@ucAc[ap@ab@ww@{Uqg@{AgDei@k_Au^{t@wNuY_Twb@uOuZei@ecAeTya@smCajFyAgDq{@{hBo{BeiE_yCouFmmA_eCkp@_{A{_@iw@es@_{A}x@qdBokBabEkk@smA{bB_nDud@gbAky@mgBgx@qdBehAg`Ckz@_fB_w@ccB_mAwiCurAyrC_iCqtFgDaHkAwC{AiCsFyL{AyC_IqQ{AwCsF{L{AgCsFiM{AiCsK{U{AwCgIsQyAwCaIsQyAgCgIsQ{AwCsFyL{AyCsFyLsAiCsFyL{AwCsF{L{AwCsFyL{AwCkAiCgDqHyAgCuFiMyAiCsFyLsAwC{F{LsAwCsFyL{AiCsFiM{AgCsF{L{AwCsFyL{AwCsF{LsAwCsFyLyAiCuFyLyAwCsF{L{AwCgIsQsAgCoNc[sAyC{K{UsAwCgIsQ{AwCgIcQsAwCsFyL{AyCsFyL{AwCsF{LyAwCsFyL{AiC_DoH{AiCsFyL{AyC_DaH{AwCsFyL{AwC_DaH{AyCsFyLyAiCaDoHyAiCgIqQ{AyCsKiV{AiCsP}_@{AgCgIsQ{AwCsFyLsAyCgIqQ{AiCiQm_@uFyLyAwC_DaHoYgm@gIcQ{AwCsKkV{AyCgIqQyAiCuKkVyAwCuK{UyAwC_^yv@gTuc@y[qq@sFiM{AiCgIqQsAyCsFyL{AwCsFyL{AiCsFyL{AyCsFyLsAwCgDaHyAwCuF{LyAwCaIcQyAwCsFyL{AyCgIqQsAiCsFiM{AgCgIsQ{AwCsF{LsAwCsFyL{AwCgIcQyAyCuFyLyAwCsFyL{AyCsFyLsAwCsFyL{AiC_DqHoDaHiCsFiBeE{KkVe@{@u@kAgIsQ{AwCsKkV{AiCgNc[kAwCkAyCsFgMkAyCyHaRcAwCaWeo@c[sy@kLq\\iCsGokAw}C{KgYsnAkfDumAyfDo~CylIsnAkfDqWoq@kiAk|C{iAk|CenAmdDyz@{|BafAysC{~@wiCkp@{gBet@smBkZww@wc@_gAaMa]or@qnBkUwm@olAkfDmxA_xDuvAkpDmt@ubBm}@mfBgJaSaRq[ob@_s@et@ofA{KwNoc@gn@i[se@m~@smAmmAecBs`@yj@}x@miAsvCobEmcAgvAwkAebBemKs~Nwb@gm@a{@apAiw@apAqz@{}AkQa]ej@wkAus@qeB_m@ebBmd@iuA}Skt@aHkVaIsZiBcGaCoIu@wCgXyjAq{@_mEkQikAeTy_Be~@ogJ_c@knEyLyjAmUo{B{@_Im@sFeEce@{Fgn@yGco@aNgwA{Zc`D{e@a`FoI_}@mcAubKshAmfLkVg_Cm@aHkA{KkmBylRsBoScAmJiCwXsPebB}T}{B}Dia@cGil@wHaq@cGed@kVi_BwN_}@_c@ytBcVqdAuYkjAs`@iuAecAejD}dDsaLuOed@qRmj@{Pag@aBeEcVso@oYqp@mJ_TwScf@q~A_cDcv@coAuh@gw@ca@yk@qu@gbAa]ib@aa@ce@o^k`@av@yv@mrBmqBs{CqwCy{@c{@um@ik@yiBmgB{vCwsC_xEwqEst@mt@keDqbDu{G_uGysC{pCky@cz@s`@o^oXyVmy@uy@spDalDaqDonD}t@iv@y`@gc@uxAscBmx@ubA}x@qeAa\\wc@{y@_gAsLeOcVs[sVs[mJgMcKiMeUeZmJyLubA_rAmUsZgw@ecA_JkLal@yu@eJkLck@{t@{j@}s@}IkL}^qf@mi@_r@oImKg^ce@gIkKwHmKyH{JwH}JyH}JwHkKgI}JqRiWcVeZmOoScF_Iu@kAqHoJoHmJ{G}IyG_JmO}SkF_IufCsaDsKyMwH{JmJ{LcGoHwHmKiIkK_IkK}OoTuDeEmJiMyf@un@gTeY{Uc[cGaIaG_IoO}SaGoIkG_JyG}IiG_JoYia@cQ{VoHkKsQyWqH{KgHkKqH{KwH{KqHkL_I{KqHiLqRgYgIiL_SeZgI{LoScZoI{LwSq[uIiMoIiM_JyMuIiM}Ta\\wIyM}_@yk@eJwM}IgNgJyM}IwM{_@kk@wIiM_JwMuIyM_JiMmTq\\_JiMuIwM_JiM}^kj@}Tq\\e_@mj@}IwMwIiM}IwMgIiM}_@kk@eJwM_JyMal@ey@uJiMeJgMapAcdBwqAaeBqVq\\}JwM}JyMu}@emAy{@{iAkcAksAa]ed@aMuOsVq\\qVq\\oJyM{JiMuJwMsVs[mJwM}JiMmJiMob@{j@mJyMgn@cy@cKiMuJiMeKyM{JiMoc@{i@sp@ww@q`@ce@oh@il@iXuZoq@yu@yq@ku@_XsZwXeZ{KyL{K{L}d@_h@{KyLoXeZ{KyLsK{L{e@mh@sK{LwXsZ{KyLsp@}s@ed@ag@iWwXiLyMuKiLed@ag@cKyLeJkLeKyLyLgO}TgX{Us[cVq\\gJwMkV_^cQgXiLuPcLsPkL_SeJuOm_@cq@_DaGwNiX_IeOgSk`@yRia@aRya@aRya@e}E_pLmPed@sZqp@aXuo@kPia@aHuOkGePcQia@aHsPaHePqQia@aRya@wIsQiHuNwHePgIePqRy`@gIuOwHuOaIgOo]cp@gSk_@wS__@gIuNoIwNoIgNoIgO}S_^eUk_@yRc\\uIgNwh@q{@gIgNwIgNmIwN__@gm@{i@a|@gIgNwIgNgIgNwIwMoIiNuIgNwSo]wIgNuEaHaMmTuIiNgTm^m_@en@uIgOwSk`@oIeOgSk`@_IePee@ecAwHeOaHuPyGcQ}Yms@_Y{t@yGcQ}Ouc@iWiw@wNce@sUww@iNse@yFaRuUux@{FqRgNse@{FaR_Nse@{FaRgNse@{FqRsUgx@wNsd@{FsQiWiv@}Ouc@iGcQ{GuPqGsPaHsP}Yms@iHePoHePiHcPqHePq\\qq@_IuOwHeOgIuOaIwNmIeOg^gn@gT_^{_@gm@mJuN}Tc\\eKwMeJgNsVs[ob@mi@aWuZ}JyL}JkLyWuYkK{K{d@af@s_Ak_A{KkL{K{KsK{K{K{KuK{K}XwXuK{Kur@ms@cL{K{K{KkLkLse@qf@iL{Kwr@ms@cL{K{e@sf@iLiL{K{K{KkLkL{KcLiL{KkLmYuY{K{K}s@}s@qf@ag@{KkLkL{K{KiLcLkL{K{KcL{KsKiLur@_s@uK{KwXwXkK{KqL{KuKkL{K{KsK{K{e@af@oXwX{e@se@sK{K{e@cf@wXuYsnAsnA{KkLif@qf@{e@cf@cLiL}XgYe_A{_AeYeYkLkLwXwXiLiLwXgYkLkLwXeYcL{KcLkLqf@ag@{KiLcLkL_YgY{KyLoXeZsKiMcLgMgXe[{KgMsKiMaXs[iWq\\q{@mhAuJgNiWo]uJwNcKgNuJwNuJwNuJgNuJwNeJwN{U}^gJwNsUk_@wIgOmJeO}Tm_@eT{_@oIgOoIuO_T{_@wSk`@_Sk`@oIePg]or@iSib@wHsPgIsPi\\{t@s[os@waAqxBs[ms@_IuPun@gvAwHcPee@sdAiHuPwHsPs[}s@wRgb@qHcQi\\mt@qHsPwHcQcGyLeUcf@oHsP_IsPs[}s@s[_s@aHsPke@ucAaHsPqHsP_IePoHePyHsP_IePgSia@oIeP_IcPwS{`@o^aq@}Sk`@oTm_@gIwN}IeOwIeO}T__@}T}^eJuNmJwNgJwNmJgNeJwNcQiWuO}TyoAijBeJgNyl@q{@eJgN{Uo]gJgNwl@q{@wg@ku@iCuDuEsGaaIanL_vG{sJ_zBskDqq@cdAk`@il@s`@ik@wv@qfAya@{j@i\\ed@ey@aeAmlB_{B_{BslCkp@yu@wq@ku@}}@y`A_YuYePcQ{cAceAucA_fAc}Ai_B_ZuZy{Hq|Hs}BayBk|GgpGib@{_@uToT_YgXg]a\\us@_s@u^m_@w{Ay~Agn@sp@or@wv@slC}{Cky@{~@auAuaB_bAemAc[__@oN_Sm_@}h@k`@mj@kf@ap@}m@cz@mUe[}Sa\\{QwXkj@kt@}IkLse@sp@{o@}|@skDowEugBcbC{d@kj@iCgDoNsQ{y@sdAa}HaoK{gCejDmi@{t@cxBsvC}aFe{GglJgiM_zHkhKy_AiuAql@ux@eaCodDmn@gw@_^se@swBcwCgxD}lFsKeOsQwXqV}^gIiN{PeYyWed@}c@{t@aqAcxB{o@afAgg@a{@su@unA{d@yu@wXwm@ir@opAeJaRog@seA}Zoq@wW{j@gYil@al@yjA{hBs`EadBmxDy`Ak}Ba`AswBy\\os@i`B_nDmTed@yfEwaJ{e@ecAyrCefGydA_{B}d@a|@y[um@{cByrCqf@q|@ca@{s@kiAsmBoc@ww@so@mhAow@oqAsj@m~@ud@kt@o_CcvDsPyWexEarHoeGqzJyfEybH_m@gbAsLqRusDycGocE__HiG}J}rA_{B{oEspHsrF}~I}s@ulAy\\il@_^so@}w@{~A{k@umAouAaxCurA}oCoyCasGy`FsnKui@ikAg]kt@{Uag@k\\il@eYaf@qWgc@g^mi@s_@{j@{[wb@qa@_i@_^y`@wg@yk@ca@{`@mOgOqW{UgXkVoN{Ksj@uc@iw@kj@qz@mj@ypAor@kt@m^iaAia@ke@uPqW}IeOsFwlAm_@}IiC_^iLcdB}i@}w@wXmPcF}JiC}pBag@q}C{~@ia@}Jag@wNs[oIoaAwWwh@iNy[mIuTeF{VcGi`A{TsVcGiz@mU_YoI{aDqeAomIgsCs_@{LuOsF{cByk@uuH{gCkaHcbC{yEy~Aog@sP{_As[soEuxAccFqdBolFqdBqGyBm}Aqf@mnIy|CelGi~Bmd@eP}qAwb@{j@uOya@kLwXaHus@_Ssz@_TcVcGwv@}SqtBuo@kbCux@_zGsaCsxBmt@eiDgkAkiBun@or@kV_{Ami@ifA{`@ww@sZ{s@wXet@gY_wA}i@_fB_r@g]iMu^iMwXmJwTqGsUqGyRuFc[}IebBce@qk@uOm_@kLgc@wNqf@sPoSaHo|@c[oc@gOolAia@gw@iWggAo]scK{|Cc`Dw`Ae}Aee@eqBum@udNmdEkhYivI_lFy_BmeCku@kz@kUkeEogAazA{`@ab@iLse@gNyk@cQ_m@cRkp@mTya@gNed@uOaq@kVa{@a\\ox@q\\ssAil@ei@kVsu@m_@ulAum@_s@k`@qzAq{@_x@sf@{n@ia@onDg_CqpAcz@u_CwaBq_CoeB_b@sZiaAcp@k{LibIib@gXib@iWed@yWed@kVce@kVgfBq{@_dCcnAcuAaq@yaMqiGoNaHg|@gc@{|GygDk}B{iAeJsFwN}I}jH_xDq|D{sB}^}Sy\\qRsUgN{[mTc[kV}}@yv@quAikAi\\gXg]kVk[mTg^mUw]qRsbCmqA_^cRmd@iVuc@{Vi\\qRm_@yVy\\{Vg]iWk\\yWy[gXuYiWk[gYs`@k`@}Zq[eYuZuTyV}TiW{hBiuBigDg|DwSkV}iNydPeoHmsIsUwXiXc[s|Gm_IwnCu`Di]gb@}]ed@s\\ud@{Zwc@w]}h@mYse@qXud@i[ik@qXoh@wX}i@iWkj@oXwm@aWum@c\\cz@qLc\\qRkj@qRil@mT_r@_IwX{z@y|CiRor@{j@uwBgSgw@wSsy@qViaA_cAe~DgNmi@uNag@_Oqf@mOud@{Pse@aS_h@wS_h@kV}i@af@gaAso@soAgYoh@e_@aq@kp@yiAw|@qzAcPiXieBcvC}OyWuc@{t@kVwb@{Uud@gY}i@gX{j@cVmi@mU}h@cVwl@}Til@uTgm@gSgm@ePag@mOag@gNcf@_Okj@qLse@uJ{`@eJia@uJgc@mJuc@aX_rAsUulAoIcf@mJ}i@uJum@iHoh@aHik@iGoi@mFmi@{E{i@eE}i@gEik@wCqg@oC{j@_Ei`AmDa|@}E}qAeEcdA}EsdAcF_}@kGsdAuEso@{Eeo@mEag@yBwW_Dc[gDe[_Eo]sFud@cGgb@c_AajG_b@_oCoJmh@{Kag@kKk`@wMgc@gOib@cPia@urAe`DiXco@uc@yaAmU_g@mYgm@i]cq@qzAeuCuNwXuP_]eTyb@wlA}eCaWag@gX_h@k\\ik@gSa]oN{UkPiW}EqHeUo]gX}_@w]af@{[ib@s_@ce@e_@wb@w]k`@e`@ka@q`@{_@se@ed@su@qq@k|CslCm^c[ee@ya@sd@ia@wvAoqAq~BewBqRcQytAapA}eH_tGik@_h@yl@oh@av@en@}s@mj@yk@gc@}i@{_@o|@il@}x@oh@{t@wb@utDevBo{EqnC_oC{}Ail@q\\gn@o]iu@wb@iuAiw@c`Akj@cz@se@o]aRw|@uc@}mAyl@m}@wb@}OqHspDyhBctAor@y{Hu~DaqAcq@sfHiqDcFiCm|KyyF}x@gb@y}ByjA{}BkjAag@eYuYePsj@c[cyAcz@}TkL{e@wXct@m_@ymDgjBcz@wb@itAgn@e_Awb@iu@_^i{@wb@}s@m_@{cBm}@ycB}~@ig@wXmgBgaAgTyMwRgNePwMgSaRaRaS_IoIwIkK}O}TmOyVoNyWkLmUsK{Uqp@azAaNeZ{KkV}Nq\\}J}TyLgXeKmUqLyWsK{UcLiW{KyV{KkVkLyWkKmUuOo]oIaReOsZwNyWaNoTwM_SuOmT}OaSkPaRiR_SuOgO_J_I}J}IuJaImJoHqLoIaMoIw^mUw`Aen@y{@kj@s[qRob@wXmd@eZud@s[ed@a\\{Z}TgYmToX_TaaAux@g^c[m^q\\k~AuwA{gBebBasCgjCw|@ex@md@m`@mZ{U{`@c[ei@{`@og@m^sf@c\\qu@ce@en@{_@q_CuwAm~DqcC{iA_s@qdBqeAu{BiuAmgAaq@aIeFiGuDaaAyl@kcBkhAakEgtC}i@m_@_~C_pByg@wXaf@iWcf@}U_IuDmgBiv@i{@o^a\\wNgDyAsk@iXsmAen@mdA}h@oWwNgTiMgSgNcQwN{V_TuT}ToX_]cVq]{Uy`@_NyWgOs[mJ}ToI}TeJgXqH{U{Pgm@ijAmdEoNse@qM{_@_N_^wN_^aWyk@gNs[cRo^aRq[aMoSgNoSePoSeOeP{PePyQwNgOkKmO}IsQoIsPaHuOuE}OuEmOgDa\\cF_n@oImx@iMaNwCaMyCiQsEaSeFko@cQq\\mJ_YoIuToH{U_IgTaI}NmIwNoIqM_JkLoIwRuO}OuNsPuPaMwMkLyMqLuOmKgNcu@qeA_}@apAk`@kj@sZ{`@gDwD{P_SwSoS_TcQgSeOeUwNaWyMsUkKmU_J{UoHuUsFeTeE_TgDqRkBiVyA_T}@wsDcGwWm@kWkAiWgCuYgEuYsFo^oIgcDiv@_^}I}Y}IgYmKmToIuT{J_TmK}SyLwSyLoSiMyRgNqRwNiRePaRsPqQcQkQaR{PaRuPaSyLuO{KuOcKwNsLaRmJeO}JsPmTka@sK}TeKkUyLwYaRed@uY}r@wXms@iq@}gBqR}h@e@{AyRyk@_Syk@_ImUeZ{_AwYw`AmDiN}EaQuEcRkF{UkGeYsFgYkFeZmEwXeEgX}Dc\\oDsZiCuYgCeZsBuZiBsZkAuZkA}^}@o^Um^uEsvM]_h@e@a\\}@wXkAgYcBgXqBeZwCq\\oDc[gD{VmEgXsFgY{FwWsFiWwIc\\{Ja\\sLo^kKsZi]m~@ov@opBgYiu@g^wbAy[y_Aqb@unAcu@uuByLm_@_Syk@sdAmzCgTil@oMc\\oNq\\aNuY}IaRwD_IeOwX}OgYsPwXaReYcQkWcRyV_SyVyRmUeTmUgS}SgToS}TqRkUqReUcQmUePwRgMmUwNgSkL{_Aog@_|Aey@arC}|AeAm@qk@se@iB{AsA{@q]{Vyp@m_@_XoS{KmJaIaHaGoI_IuNiIuPsFaRsEoSiCkU{AgY]{Ul@}TzAoTpBaQfDaSxf@smBtIs[jG}SlZuy@nSgm@hGqQdFiM`HwNpGiMxRm_@`GyLvD}JtDcP`CePd@uE|@mJpBq\u000bCia@bBoSpBsQvCaRpCgNvCwNroAe~EpVebArQos@rZgkAtPsp@hLwb@jQ}i@lJcZ`]wx@`\\ex@f^i`Ar[uy@nSik@vRgm@j`@qpAj[sdAnNag@tZm}@lTso@vc@oqA~BaHpCcGvCcF~CgEnDeEvDuDtDiCvDyBtDiBdE{AvD}@nDm@tD]nD]dE?|DNdF\nIz@hLzAzLjBhLhBrLxBpLhCzZ`HlKvChLfDtKfD`LtDtKvDhLdEfIfDtEhBjFxCfEfCdDxCvDdE~CrFpBbGzA`Ht@nHLpGEbGe@pG}@bG{ArFqBtEiCtE_DfDmDvCwDxB_D|@_Dl@gDLgD]_Dm@qCkAaCkBoCgCiH_J{PaR}DuD_EyCwWwMi|@mi@{EwDmEgDmEeEwDeE}DaHwDoIgDmJoC}JkB{KkAiMe@uN?yMVwNr@yLzAwMxBkLpC}Jz}F}~Q`iGuyRzEuOlo@krBpBqHbB_IxAoIt@qHhCiLr@eFlAqGbAuEjAeEvH{UhCiM\\sFe@sFkAeEqBgDwCkBsLgD{EuD{GeFoRgMrFcQpWsz@rAeEjFuPx_AoxCse@s[aHlT");

    // repeated steps
    const std::array<float, 31> distances = {{0.032,1.28,0.494,0.307,0.733,0.36,3.079,0.863,3.301,3.669,0.659,43.486,0.485,14.977,12.472,83.573,1.762,1.173,0.249,7.259,181.193,0.269,0.855,3.652,2.424,0.097,0.168,0.394,0.079,0.033,0}};
    const std::array<std::uint32_t, 31> durations = {{2,118,64,56,41,28,166,40,146,165,28,1814,34,669,471,2965,74,48,10,304,6320,26,35,191,99,4,8,81,37,10,0}};
    const std::vector<std::vector<const char*>> street_names = {{ "H Street Northwest" }, { "15th Street Northwest" }, { "Raoul Wallenberg Place Southwest" }, { "Maine Avenue Southwest" }, {}, { "I 395 North", "Southwest Freeway" }, { "I 695" }, { "I 695" }, { "DC 295 North", "Anacostia Freeway" }, { "Kenilworth Avenue Freeway" }, {}, { "MD 295 North", "Baltimore-Washington Parkway" }, {}, { "I 895 North" }, { "Express Toll Lanes" }, { "I 95 North" }, { "I 295" }, {}, {}, { "I 295 North" }, { "New Jersey Turnpike" }, {}, {}, { "NJ 495" }, { "Lincoln Tunnel" }, {}, {}, { "West 40th Street" }, { "8th Avenue" }, { "West 41st Street" }, {} };

    // repeated maneuvers
    const std::array<std::string, 31> maneuvers = {{ "Depart", "Turn", "Continue", "Turn", "Turn", "Merge", "Fork", "Turn", "Merge", "Continue", "Turn", "Merge", "Turn", "Merge", "Continue", "Continue", "Fork", "Turn", "Fork", "Merge", "Fork", "Turn", "Fork", "Merge", "Bear", "Turn", "Fork", "Turn", "Turn", "Turn", "Arrive"}};
    const std::array<int, 31> bearings_before = {{0,178,108,177,177,94,90,147,60,2,102,82,85,331,320,4,52,5,98,23,39,64,67,112,45,60,25,25,23,104,119}};
    const std::array<int, 31> bearings_after = {{180,88,178,180,165,88,88,153,57,26,105,85,85,336,329,2,59,14,102,21,37,64,70,109,43,56,32,30,26,111,111}};
    const std::array<std::string, 31> instructions = {{ "Drive east on H Street Northwest.", "Turn right onto 15th Street Northwest.", "Continue on Raoul Wallenberg Place Southwest.", "Turn left onto Maine Avenue Southwest.", "Take the I 395 North ramp on the left.", "Merge onto I 395 North\\/Southwest Freeway.", "Keep left to take I 695.", "Take the DC 295 North exit on the right toward US 50.", "Merge onto DC 295 North\\/Anacostia Freeway.", "Continue on Kenilworth Avenue Freeway.", "Take the Baltimore Washington Parkway exit on the left toward I 95.", "Merge onto MD 295 North\\/Baltimore-Washington Parkway.", "Take the I 895 North exit on the right toward Baltimore Harbor Tunnel Thruway.", "Merge onto I 895 North.", "Continue on Express Toll Lanes.", "Continue on I 95 North.", "Keep right to take I 295 toward Delaware Memorial Bridge\\/New Jersey\\/Newport.", "Take the US 13 North exit on the left toward Wilmington.", "Keep right to take I 295 North toward NJTP\\/Delware Memorial Bridge\\/New York-New Jersey.", "Merge onto I 295 North.", "Keep left to take New Jersey Turnpike.", "Take exit 16E on the right.", "Keep right at the fork.", "Merge onto NJ 495.", "Bear right onto Lincoln Tunnel.", "Take the exit on the right toward Dyer Avenue.", "Keep left toward NY 9A\\/42nd Street\\/Uptown\\/Theater District.", "Turn right onto West 40th Street.", "Turn left onto 8th Avenue.", "Turn left onto West 41st Street.", "Your destination is on the left." }};
    const std::array<const char*, 31> verbal_alerts = {{ nullptr,  "Turn right onto 15th Street Northwest.",  "Continue on Raoul Wallenberg Place Southwest.",  "Turn left onto Maine Avenue Southwest.",  "Take the Interstate 3 95 North ramp on the left.",  nullptr,  "Keep left to take Interstate 6 95.",  "Take the D C 2 95 North exit on the right.",  nullptr,  "Continue on Kenilworth Avenue Freeway.",  "Take the Baltimore Washington Parkway exit on the left.",  nullptr,  "Take the Interstate 8 95 North exit on the right.",  nullptr,  "Continue on Express Toll Lanes.",  "Continue on Interstate 95 North.",  "Keep right to take Interstate 2 95.",  "Take the U.S. 13 North exit on the left.",  "Keep right to take Interstate 2 95 North.",  nullptr,  "Keep left to take New Jersey Turnpike.",  "Take exit 16E on the right.",  "Keep right at the fork.",  nullptr,  "Bear right onto Lincoln Tunnel.",  "Take the exit on the right toward Dyer Avenue.",  "Keep left toward New York 9A.",  "Turn right onto West 40th Street.",  "Turn left onto 8th Avenue.",  "Turn left onto West 41st Street.",  "Your destination will be on the left."}};
    const std::array<const char*, 31> verbal_pres = {{ "Drive east on H Street Northwest for 30 meters. Then Turn right onto 15th Street Northwest.",  "Turn right onto 15th Street Northwest.",  "Continue on Raoul Wallenberg Place Southwest for a half kilometer.",  "Turn left onto Maine Avenue Southwest.",  "Take the Interstate 3 95 North ramp on the left.",  "Merge onto Interstate 3 95 North, Southwest Freeway.",  "Keep left to take Interstate 6 95.",  "Take the D C 2 95 North exit on the right toward U.S. 50.",  "Merge onto D C 2 95 North, Anacostia Freeway.",  "Continue on Kenilworth Avenue Freeway for 3.7 kilometers.",  "Take the Baltimore Washington Parkway exit on the left toward Interstate 95.",  "Merge onto Maryland 2 95 North, Baltimore-Washington Parkway.",  "Take the Interstate 8 95 North exit on the right toward Baltimore Harbor Tunnel Thruway.",  "Merge onto Interstate 8 95 North.",  "Continue on Express Toll Lanes for 12.5 kilometers.",  "Continue on Interstate 95 North for 83.6 kilometers.",  "Keep right to take Interstate 2 95 toward Delaware Memorial Bridge, New Jersey.",  "Take the U.S. 13 North exit on the left toward Wilmington.",  "Keep right to take Interstate 2 95 North toward NJTP, Delware Memorial Bridge.",  "Merge onto Interstate 2 95 North.",  "Keep left to take New Jersey Turnpike.",  "Take exit 16E on the right.",  "Keep right at the fork.",  "Merge onto New Jersey 4 95.",  "Bear right onto Lincoln Tunnel.",  "Take the exit on the right toward Dyer Avenue. Then Keep left toward New York 9A.",  "Keep left toward New York 9A, 42nd Street. Then Turn right onto West 40th Street.",  "Turn right onto West 40th Street.",  "Turn left onto 8th Avenue. Then Turn left onto West 41st Street.",  "Turn left onto West 41st Street. Then Your destination will be on the left.",  "Your destination is on the left."}};
    const std::array<const char*, 31> verbal_posts = {{ nullptr,  "Continue for 1.3 kilometers.",  nullptr,  "Continue for 300 meters.",  nullptr,  "Continue for 400 meters.",  "Continue for 3.1 kilometers.",  nullptr,  "Continue for 3.3 kilometers.",  nullptr,  nullptr,  "Continue for 43.5 kilometers.",  nullptr,  "Continue for 15 kilometers.",  nullptr,  nullptr,  nullptr,  nullptr,  nullptr,  "Continue for 7.3 kilometers.",  "Continue for 181.2 kilometers.",  nullptr,  nullptr,  "Continue for 3.7 kilometers.",  "Continue for 2.4 kilometers.",  nullptr,  nullptr,  "Continue for 400 meters.",  "Continue for 80 meters.",  "Continue for 30 meters.",  nullptr}};
        // signs
    const std::array<bool, 31> signs = {{0,0,0,0,1,0,0,1,0,0,1,0,1,0,0,0,1,1,1,0,0,1,0,0,0,1,1,0,0,0,0}};
    const std::array<const char*, 31> exit_numbers = {{nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,"16E",nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr}};
        // exit toward elements
    const std::array<std::vector<std::string>, 31> exit_toward_locations = {{{},{},{},{},{},{},{},{"US 50"},{},{},{"I 95"},{},{"Baltimore Harbor Tunnel Thruway"},{},{},{},{"Delaware Memorial Bridge", "New Jersey", "Newport"},{"Wilmington"},{"NJTP","Delware Memorial Bridge","New York-New Jersey"},{},{},{},{},{},{},{"Dyer Avenue"},{"NY 9A","42nd Street", "Uptown", "Theater District"},{},{},{},{}}};
        // exit branch elements
    const std::array<std::vector<std::string>, 31> exit_onto_streets = {{{},{},{},{},{"I 395 North"},{},{},{"DC 295 North"},{},{},{"Baltimore Washington Parkway"},{},{"I 895 North"},{},{},{},{"I 295 Northbound", "DE 141 Northbound"},{"US 13 North"},{"I 295 North"},{},{},{},{},{},{},{},{},{},{},{},{}}};
    const std::array<std::vector<int>, 31> exit_onto_streets_cc = {{{},{},{},{},{1},{},{},{1},{},{},{},{},{1},{},{},{},{},{},{1},{},{},{},{},{},{},{},{},{},{},{},{}}};

    const std::array<int, 31> geometry_indices_begin = {{ 0,  2,  59,  81,  93,  134,  137,  209,  233,  305,  381,  395,  920,  935,  1150,  1223,  1977,  1989,  2005,  2008,  2054,  3838,  3843,  3863,  3969,  3990,  3996,  4006,  4011,  4012,  4013 }};
    const std::array<int, 31> geometry_indices_end = {{ 2,  59,  81,  93,  134,  137,  209,  233,  305,  381,  395,  920,  935,  1150,  1223,  1977,  1989,  2005,  2008,  2054,  3838,  3843,  3863,  3969,  3990,  3996,  4006,  4011,  4012,  4013,  4013}};

    std::size_t i = 0;
    while (i < 31)
    {
        // STEPS
        // =====================================================
        Step* step = leg1->add_steps();

        step->set_distance(distances[i]);
        step->set_duration(durations[i]);

        step->set_geometry_index_begin(geometry_indices_begin[i]);
        step->set_geometry_index_end(geometry_indices_end[i]);

        step->set_incoming_maneuver_index(i);
        step->set_outgoing_maneuver_index(i);

        // street names
        if (!street_names.at(i).empty())
        {
            for (const char* s : street_names.at(i))
            {
                StreetName* ssn = step->add_street_names();
                ssn->set_text(s);
            }
        }

        step->set_travel_mode("drive");
        step->set_travel_mode("car");
        step->set_travel_mode("right");

        // MANEUVERS
        // =====================================================
        Maneuver* man = leg1->add_maneuvers();

        man->set_type(maneuvers[i]);
        man->set_incoming_bearing(bearings_before[i]);
        man->set_outgoing_bearing(bearings_after[i]);
        // street name
        if (!street_names.at(i).empty())
        {
            for (const char* s : street_names.at(i))
            {
                StreetName* man_sn = man->add_street_names();
                man_sn->set_text(s);
            }
        }
        if (signs[i])
        {
            Sign* man_sign = man->mutable_sign();
            if (exit_numbers.at(i) != nullptr)
            {
                auto se = man_sign->add_exit_numbers();
                se->set_text(exit_numbers.at(i));
            }
            if (!exit_toward_locations.at(i).empty())
            {
                for (const std::string &x : exit_toward_locations.at(i))
                {
                    SignElement* setl = man_sign->add_exit_toward_locations();
                    setl->set_text(x);
                }
            }
            if (!exit_onto_streets.at(i).empty())
            {
                bool has_cc = !exit_onto_streets_cc.at(i).empty();
                std::size_t j = 0;
                for (; j < exit_onto_streets.at(i).size(); ++j)
                {
                    SignElement* setl = man_sign->add_exit_onto_streets();
                    setl->set_text(exit_onto_streets.at(i).at(j));
                    if (has_cc)
                    {
                        setl->set_consecutive_count(exit_onto_streets_cc.at(i).at(j));
                    }
                }
            }

        }
        // TODO lane
        // obvious - skip for now
        // is verbal multi cue - skip for now
        man->set_text_instruction(instructions.at(i));
        if (verbal_alerts.at(i) != nullptr)
        {
            man->set_verbal_transition_alert_instruction(verbal_alerts.at(i));
        }
        man->set_verbal_pre_transition_instruction(verbal_pres.at(i));
        if (verbal_posts.at(i) != nullptr)
        {
            man->set_verbal_post_transition_instruction(verbal_posts.at(i));
        }

        i++;
    }

    // write to file
    std::ofstream OutputFile("dcny.route.pbf");
    if (!OutputFile)
    {
        throw std::runtime_error("Unable to open write file");
    }
    auto wrote = miz.SerializeToOstream(&OutputFile);
    if (!wrote)
    {
        throw std::runtime_error("Unable to serialize to file");
    }

}
