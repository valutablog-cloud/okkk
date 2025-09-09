
function NewMessage() {

    var result = ehbridge.bridge('');

    result = result[0];

    var msg = result = result.substring(9, result.length);

    msg = result.substring(0, result.indexOf("</message>"));

    result = result.substring(result.indexOf("</message>") + 19);

    result = result.substring(0, result.indexOf("</details>"));

    var tmp = result;

    result = msg;

    var details = tmp;

    
    if (result == "B_VERSION") {

        $.bversion(details);

    } else if (result == "B_DATE") {

        $.bdate(details);

    } else if (result == "CHANGE_VIEW") {

        $.changeView(details);

    } else if (result == "SETPREMIUMINFO") {

        $.SetPremiumInfo(details);

    }else if (result == "SETCOUNTRYANY") {

        $.SETCOUNTRYANY();

    } else if (result == "SETCITYANY") {

        $.SETCITYANY();

    } else if (result == "SETRESIDENTIAL") {

        $.set_residential(details == "1");

    } else if (result == "COUNTRY_CITY_LIST") {

        $.COUNTRY_CITY_LIST(details);

    } else if (result == "REMOVEALLREGIONSFORISO") {

        $.REMOVEALLREGIONSFORISO(details);

    } else if (result == "REFRESH_COUNTRY_REGIONS") {

        $.RefreshRegionsCountries();

    } else if (result == "SETLOGOUT") {

        $.SetLogOut();

    } else if (result == "ENABLEDISABLELOGINBUTTON") {

        $.EnableDisableLoginButton(details);

    } else if (result == "EVENTSETCONTROL") {

        $.RecvEventChange(details);

    } else if (result == "ACTIVATEIPLIST") {

        $.EnableSwitch = true;

    } else if (result == "DEACTIVATEIPLIST") {

        $.EnableSwitch = false;

    } else if (result == "SETPREMIUM") {

        $.SetPremium(true);

    } else if (result == "SETFREE") {

        $.SetPremium(false);

    } else if (result == "SETSETTINGS") {

        $.SetSettings();

    } else if (result == "ADDIP") {

        $.AddIP(details);

    } else if (result == "REMOVEIP") {

        $.RemoveIP(details);

    } else if (result == "IPLISTVISIBLE") {

        $.SetIpListVisibility();

    } else if (result == "SETCURSOR") {

        $(".slick-cell").attr('style', details);

        $.cursor = details;

        $.SetIpListVisibility();

    } else if (result == "HIGHLIGHT") {

        $.HighLight(details);

    } else if (result == "SETMYIP") {

        if (details == "CLEAR") $.SetMyIp();

        else $.SetMyIp(details);

    }else if (result == "SETCURRENTIP") {

        $.SetCurrentIp(details);

    } else if (result == "CLEARLIST") {

        $.ClearList();

    } else if (result == "SETEXPIRES") {

        $.SetExpire(details);

    } else if (result == "SETEMPASS") {

        $.SetLoginPass(details);

    } else if (result == "ADDCOUNTRY") {

        $.AddCountry(details, false);

    } else if (result == "ADDCOUNTRY_CHECKED") {

        $.AddCountry(details, true);

    } else if (result == "ADDREGION") {

        $.AddRegion(details, false);

    } else if (result == "ADDREGION_CHECKED") {

        $.AddRegion(details, true);

    } else if (result == "REMOVEREGION") {

        $.RemoveRegion(details, true);

    } else if (result == "REMOVECOUNTRY") {

        $.RemoveCountry(details, true);

    } else if (result == "REMOVEREGION_ONLY_IF_UNCHECKED") {

        $.RemoveRegion(details, false);

    } else if (result == "REMOVECOUNTRY_ONLY_IF_UNCHECKED") {

        $.RemoveCountry(details, false);

    }
}
