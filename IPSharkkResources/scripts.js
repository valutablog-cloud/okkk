
$(document).ready(function () {

    $(document).on('click', '.toggle-button', function ()
    {
        $(this).toggleClass('toggle-button-selected');

        var send = "<message>RESIDENTIAL_CHANGED</message><details>" + ($(this).hasClass('toggle-button-selected') ? "1" : "0") + "</details>";

        ehbridge.bridge(send);
    });

    var send = "<message>RESIDENTIAL_SET</message><details></details>";

    ehbridge.bridge(send);

    $.set_residential = function (is_residential)
    {
        if (is_residential)
            $("#residential-id").addClass("toggle-button-selected");
        else
            $("#residential-id").removeClass("toggle-button-selected");
    }

    function formatCountry(row, cell, value, columnDef, dataContext) {

        return "<div><div class=\"left\"><img class=\"image\" src=\"" + dataContext.url + "\" /></div><div class=\"right\"><p>&nbsp;" + dataContext.country + "</p></div></div>";
    }

    function objLength(obj) {

        var i = 0;

        for (var x in obj) {

            if (obj.hasOwnProperty(x))
                i++;
        }

        return i;
    }

    $.country_city_list = [];

    $.COUNTRY_CITY_LIST = function (details) {

        var objm = $.parseJSON(details);

        var countries = [];
        var cities = [];
        $.country_city_list = [];

        for (var i = 0; i < objLength(objm[0].list); i++) {

            var obj = objm[0].list[i];
            var iso = obj.iso;
            var full = obj.full;
            var img = obj.img;

            var country_ = [];
            country_.push(iso);

            //add country

            for (var i2 = 0; i2 < objLength(obj.cities) ; i2++) {

                var city = obj.cities[i2];
                country_.push(city);
            }

            if (i == objm[0].country_selected_index) {

                countries.push([iso, full, "qrc:/images/flags/flags/"+img+".png", true]);

                //select this ccountry

                for (var i2 = 0; i2 < objLength(obj.cities); i2++) {

                    var city = obj.cities[i2];

                    //add city

                    if (i2 == objm[0].city_selected_index) {

                        //select this city
                        cities.push([city, true]);
                    }
                    else
                        cities.push([city, false]);
                }
            }
            else
                countries.push([iso, full, "qrc:/images/flags/flags/" + img + ".png", false]);

            $.country_city_list.push(country_);
        }

        updateCountries(countries);
        updateCities(cities);
    }

    $.ClearList = function () {}

    $.SetExpire = function (details) {

        if (details == "hide")
        {
            $('#expire').hide();
            $('.center_').css('top', '100px');
        }
        else
        {
            $('#expire_days').html(details);
            $('#expire').show();
            $('.center_').css('top', '60px');
        }

        AdjustSize();
    }

    $.SetLogin = function () {

        $.hideiplist = true;
        $.SetIpListVisibility();
        $('#settingsbox').hide();
        $('#loginbox').show();

    }

    $.SetSettings = function () {

        $.hideiplist = true;
        $.SetIpListVisibility();
        $('#loginbox').hide();
        $('#settingsbox').show();

    }

    var customSelects = document.querySelectorAll(".custom-dropdown__select");
    for (var i = 0; i < customSelects.length; i++) {
        if (customSelects[i].hasAttribute("disabled")) {
            customSelects[i].parentNode.className += " custom-dropdown--disabled";
        }
    }

    $('#close1,#close2').each(function () {
        $(this).click(function () {

            $.hideiplist = false;
            $('#settingsbox').hide();
            $.SetIpListVisibility();
        });
    });

    $('#cancellogin').each(function () {
        $(this).click(function () {

            $.hideiplist = false;
            $('#loginbox').hide();
            $.SetIpListVisibility();
        });
    });


    $('.login:first').click(function () { });


    $.EnableDisableLoginButton = function (value) {

        $('#oklogin').prop('disabled', value == "true" ? true : false);
    }

    $.SetLogOut = function () {

        $('#email,#password').prop('disabled', true);
        $('#oklogin').html('Logout');

        $.logouttype = true;
    }

    $.EnableDisableLoginButton('true');

    $('#oklogin').each(function () {
        $(this).click(function () {

            if ($.logouttype) {

                $('#password').val('');
                $('#email').val('');

                $('#email,#password').prop('disabled', false);
                $('#oklogin').html('Login');
                $.logouttype = false;
            }

            var email = $('#email').val();
            var password = $('#password').val();

            var send = "<message>SETEMPASS</message><details>{\"idx\":{\"email\":\"" + email + "\", \"password\":\"" + password + "\"}}</details>";

            ehbridge.bridge(send);

            $.hideiplist = false;
            $('#loginbox').hide();
            $.SetIpListVisibility();
        });
    });


    $('#regid1').prepend('<div id="disableregions"></div>');
    $('#couid1').prepend('<div id="disablecountries"></div>');

    $('.headercc:first').prepend('<div id="disablecountriesheader"></div>');
    $('.headercc:last').prepend('<div id="disableregionsheader"></div>');

    $("#country-checkbox-input,#region-checkbox-input").change(function () {

        UpdateUI();

    });

    function UpdateUI() {}

    $.DisableRegions = function () {}

    $.EnableRegions = function () {}

    $.DisableCountries = function () {}

    $.EnableCountries = function () {}

    $.EnableCountries();
    $.EnableRegions();

    $.EnableControl = function (slider) {

        $('#' + slider).prop('disabled', false);
    }

    $.DisableControl = function (slider) {

        $('#' + slider).prop('disabled', true);
    }

    $.RecvEventChange = function (elid) {

        var res = elid.split(";");

        var _elid = $('#' + res[0]);

        if (res[0] == "automatic-ip-changing-settings") {

            if (res[2] == 'true') {

                $.EnableControl('change-ip-automatically-every');
                $.EnableRegions();
                $.EnableCountries();

            } else {

                $.DisableControl('change-ip-automatically-every');
                $.DisableRegions();
                $.DisableCountries();
            }

        }

        if (res[1] == "onoffswitch-checkbox-small" || res[1] == "css-checkbox") _elid.prop('checked', res[2] == 'true' ? true : false);

        else if (res[0] == "change-ip-automatically-every") {

            $('#change-ip-automatically-every').get(0).selectedIndex = (res[2]);
        }
    }

    $.SendEventChange = function (thisel) {

        var _id = $(thisel).attr('id');

        var _class = $(thisel).attr('class');

        var _state = "";

        if (_class == "onoffswitch-checkbox-small" || _class == "css-checkbox") _state = $(thisel).is(':checked') ? 'true' : 'false';

        if (_id == "change-ip-automatically-every") _state = $(thisel).prop("selectedIndex") + ';' + $(thisel).find(":selected").text();

        var send = '<message>CONTROLSTATECHANGED</message><details>CONTROLID:' + _id + ';CONTROLCLASS:' + _class + ';CURRENTSTATE:' + _state + '</details>';

        ehbridge.bridge(send);
    }

    //$.SendEventChange('#change-ip-automatically-every');

    $(".onoffswitch-checkbox-small,#change-ip-automatically-every,#country-checkbox-input,#region-checkbox-input").each(function () {

        $(this).change(function () {

            $.SendEventChange($(this));
        });

    });

    $.DelItem = function DelItem(id) {}

    $.SetPremium = function (val) {

        document.getElementById("bodyid").className = !val ? "bodyfree" : "bodypremium";

        if (!val) $('#buypro').show();

        else $('#buypro').hide();
    }

    $.SetMyIp = function (info) {

        var objm = $.parseJSON(info);

        for (var i = 0; i < objm.length; i++) {

            var obj = objm[i].idx;

            $("#countrybox").html(obj.countryName);
            $("#city").html(obj.city + ", " + obj.region);
            $("#imgbox").attr("src", "qrc:/images/flags/flags/" + obj.countryCodeImg + ".png");
        }
    }

    $.logouttype = false;

    $.SetLoginPass = function (info) {

        var objm = $.parseJSON(info);

        for (var i = 0; i < objm.length; i++) {

            var obj = objm[i].idx;

            $("#email").val(obj.email);
            $("#password").val(obj.password);

            if (obj.email.length > 0) {

                $.SetLogOut();
            }
        }
    }

    $.HighLight = function HighLight(id) {}

    $.DataItem = function DataItem(realid, country, city, region, imgurl, addid, highlight) {}


    $(function () {

        $(".tabContent").not(":first").hide();
        $("ul.tabs li:first").addClass("active").show();
        $("ul.tabs li").click(function () {
            $("ul.tabs li.active").removeClass("active");
            $(this).addClass("active");
            $(".tabContent").hide();
            $($('a', this).attr("href")).fadeIn('slow');
            return false;
        });


        $('#countries ul,#regions ul,.slick-viewport').perfectScrollbar({
            suppressScrollX: true
        });


        $(window).resize(function () {

            AdjustSize();
        });

        $("#buypro *").hover(
            function () {
                $(this).stop().animate({
                    "opacity": "0.8"
                }, "slow");
            },
            function () {
                $(this).stop().animate({
                    "opacity": "1"
                }, "slow");
            });

        $('#buypro img').click(function () {

            ehbridge.bridge('<message>OPENPREMIUM</message><details></details>');

        });

        $('#buypro button').click(function () {

            ehbridge.bridge('<message>OPENFREE_PREMIUM</message><details></details>');

        });

        jQuery.fn.center = function () {
            this.css("position", "absolute");
            this.css("top", Math.max(0, (($(window).height() - $(this).outerHeight()) * 0.6) +
                $(window).scrollTop() + 100) + "px");
            this.css("left", Math.max(0, (($(window).width() - $(this).outerWidth()) / 2) +
                $(window).scrollLeft()) + "px");
            return this;
        }

        $('#buypro img').one('load', function () {
            AdjustSize();
        }).each(function () {
            if (this.complete) $(this).load();
        });


        $.height = 400; //base height to calculate difference and stretch divs
        $.heightdiv = 44; //

        function AdjustSize() {

            var vpw = $(window).width();
            var vph = $(window).height();

            $('.prefs').css({ 'height': (vph - 145) + 'px' });
            $('.prefs').css({ 'width': (vpw - 42) + 'px' });

            var topc, leftc;

            var h = $('#container').height();

            var h2 = $('#settingsbox').height() - $.height;

            h2 /= 2;

            $('#countries ul,#regions ul').height($.heightdiv + h2);

            $('#buypro').center();

            $.SetIpListVisibility();

            $('#countries ul,#regions ul,.slick-viewport').perfectScrollbar('destroy');
            $('#countries ul,#regions ul,.slick-viewport').perfectScrollbar();
        }

        AdjustSize();

        $.AddItems = function AddItems(items) {}
    });

    $.redraw = false;
    $.reset = false;
    $.first = true;

    $.IPvis = $('#iplistswitch').is(":checked");
    $.IPloc = $('#container').offset();

    $.cursor = 'cursor: default !important';
   
    function NormalizeID(rid) {

        while (rid.indexOf(" ") != -1) rid = rid.replace(" ", "-");

        return rid;
    }

    function RestoreID(rid) {

        while (rid.indexOf("-") != -1) rid = rid.replace("-", " ");

        rid = rid.replace(" ", "-");

        return rid;
    }

    $.AddClickEvent = function () {

        $('#countries ul:first > li,#regions ul:first > li').each(function () {

            var el = $(this).find("input:first");

            $(el).unbind('change');
            $(el).change(function () {

                var rid = $(this).parent().attr('id');

                rid = RestoreID(rid);

                var send = ($(this).is(':checked') ? 'true' : 'false') + ';';
                send += $(this).parent().parent().parent().attr('id') + ';';
                send += rid;

                if (send.indexOf(" lir") == send.length - 4 || send.indexOf(" lic") == send.length - 4) {

                    send = send.substring(0, send.length - 4);
                }

                ehbridge.bridge('<message>CLICKED_REGION_COUNTRY</message><details>' + send + '</details>');
            });
        });
    };

    $.SortList = function (mylist) {

        var listitems = mylist.children("li");

        listitems.sort(function (a, b) {

            var compA = $(a).find('label').text().toUpperCase();

            var compB = $(b).find('label').text().toUpperCase();

            return (compA < compB) ? -1 : (compA > compB) ? 1 : 0;

        });

        $(mylist).append(listitems);
    }

    $.AddRegion = function (region, checked) {};

    $.REMOVEALLREGIONSFORISO = function (iso) {}

    $.RemoveRegion = function (region, always) {};

    $.AddCountry = function (country, checked) {};

    $.RemoveCountry = function (country, always) {};

    $.RefreshRegionsCountries = function () {}

    $.AddIP = function (info) {}

    $.RemoveIP = function (info) {}

    $.hideiplist = false;

    $.SetIpListVisibility = function SetIpListVisibility(setv) {

        if (!$.EnableSwitch) $('#iplistswitch').prop('checked', false);

        if ($('#iplistswitch').is(":checked") && !$.hideiplist) {

            $.IPvis = true;
            $('#container').offset({
                top: $.IPloc.top,
                left: $.IPloc.left
            });

        } else {

            $.IPvis = false;
            $('#container').offset({
                top: $.IPloc.top,
                left: ($('#container').width() * -1) - 100
            });
        }
    }

    $('#iplistswitch').change(function () {

        var ret = $('#iplistswitch').is(":checked") ? "1" : "0";

        $.SetIpListVisibility();

        ehbridge.bridge('<message>IPLISTVISIBILITY</message><details>' + (ret) + '</details>');
    });

    $.SetIpListVisibility();

    ehbridge.bridge('<message>LOADED</message><details></details>');
});


(function ($) {

    $.fn.chosenImage = function (options) {

        return this.each(function () {

            var $select = $(this),
                imgMap = {};

            $select.find('option').filter(function () {
                return $(this).text();
            }).each(function (i) {
                var imgSrc = $(this).attr('data-img-src');
                imgMap[i] = imgSrc;
            });

            $select.chosen(options);

            var chzn_id = $select.attr('id');
            chzn_id += "_chzn";

            var chzn = '#' + chzn_id,
                $chzn = $(chzn).addClass('chznImage-container');


            $chzn.find('.chzn-results li').each(function (i) {
                $(this).css(cssObj(imgMap[i]));
            });

            $select.change(function () {

                var country = $(this).hasClass("country-select");
                var val = $select.find('option:selected').val();
                var html = $select.find('option:selected').text();

                if ((country && typeof $.ccountry !== 'undefined' && $.ccountry == val) || (!country && typeof $.ccity !== 'undefined' && $.ccity == val))
                    return;

                if (country)
                    $.ccountry = val;
                else
                    $.ccity = val;

                if (country)
                {
                    for(var i = 0; i < $.country_city_list.length; i++)
                    {
                        if(val == $.country_city_list[i][0])
                        {
                            var cities = [];

                            var tmp = $.country_city_list[i].slice();
                            tmp.shift();

                            for (var i = 0; i < tmp.length; i++)
                                cities.push([tmp[i], (i == 0 ? true : false)]);

                            updateCities(cities);

                            break;
                        }
                    }
                }

                if (country)
                    ehbridge.bridge("<message>COUNTRY_CHANGED</message><details>" + html + ";" + val + "</details>");
                else
                    ehbridge.bridge("<message>CITY_CHANGED</message><details>"+val+"</details>");

                console.log("change " + (country ? "country" : "city"));

                var imgSrc = ($select.find('option:selected').attr('data-img-src')) ?
                    $select.find('option:selected').attr('data-img-src') : '';
                $chzn.find('.chzn-single span').css(cssObj(imgSrc));
            });

            //$select.trigger('change');

            var imgSrc = ($select.find('option:selected').attr('data-img-src')) ?
                $select.find('option:selected').attr('data-img-src') : '';
            $chzn.find('.chzn-single span').css(cssObj(imgSrc));

            function cssObj(imgSrc) {
                if (imgSrc) {
                    return {
                        'background-image': 'url(' + imgSrc + ')',
                        'background-repeat': 'no-repeat'
                    }
                } else {
                    return {
                        'background-image': 'none'
                    }
                }
            }
        });
    }

})(jQuery);

function checkDOMChange() {

    if ($.fn.perfectScrollbar)
    {
         $('.chzn-results').perfectScrollbar();
         $('.chzn-results').perfectScrollbar("update");
    }

    setTimeout(checkDOMChange, 1000);
}

function inArray(needle, haystack) {

    var length = haystack.length;
    for (var i = 0; i < length; i++) {
        if (haystack[i] == needle) return true;
    }
    return false;
}

function updateCountries(countries) {

    var sel = document.getElementById('country-select');

    $(sel).empty();

    var selected_opt = false;

    for (var i = 0; i < countries.length; i++)
    {
        if (countries[i][3])
        {
            selected_opt = countries[i][0];
            $.ccountry = countries[i][0];
        }

        var opt = new Option(countries[i][1], countries[i][0]);
        opt.setAttribute("data-img-src", countries[i][2]);
        sel.options.add(opt);
    }

    for (var i = 0, n = sel.options.length; i < n; i++) {
        sel.options[i].selected = false;

        if (selected_opt !== false && selected_opt == sel.options[i].value)
            sel.options[i].selected = true;
    }

    $('#country-select').trigger('liszt:updated');
    $("#country-select").chosenImage();
}



function updateCities(cities) {

    var values = [];
    var sel = document.getElementById('city-select');

    $(sel).empty();
   
    var selected_opt = false;

    for (var i = 0; i < cities.length; i++)
    {
        if (cities[i][1])
        {
            selected_opt = cities[i][0];
            $.ccity = cities[i][0];
        }

        sel.options.add(new Option(cities[i][0], cities[i][0]));
    }

    for (var i = 0, n = sel.options.length; i < n; i++) {
        sel.options[i].selected = false;

        if (selected_opt !== false && selected_opt == sel.options[i].value)
            sel.options[i].selected = true;
    }

    $('#city-select').trigger('liszt:updated');
    $("#city-select").chosenImage();
}

$.SETCOUNTRYANY = function () {

    var sel = document.getElementById('country-select');
    sel = sel.options;

    for (var i = 0; i < sel.length; i++)
        sel[i].selected = (i == 0 ? true : false);

    $.ccountry = "ANY";

    $('#country-select').trigger('liszt:updated');
    $("#country-select").chosenImage();
};

$.SETCITYANY = function () {

    var sel = document.getElementById('city-select');
    sel = sel.options;

    for (var i = 0; i < sel.length; i++)
        sel[i].selected = (i == 0 ? true : false);

    $.ccity = "Any";

    $('#city-select').trigger('liszt:updated');
    $("#city-select").chosenImage();
};

$(document).ready(function () {

    $(".infolink").hover(function () {
        $(".tooltip").show();
    }, function () {
        $(".tooltip").hide();
    });

    $("#country-select").chosenImage();
    $("#city-select").chosenImage();

    $("#next_nearby").click(function () {

        ehbridge.bridge("<message>NEXT_NEARBY</message><details></details>");
    });

    checkDOMChange();
});