
$(document).ready(function () {

    $.stars = 5;

    $(document).on('hover', '.star', function ()
    {
        var starnum = parseInt($(this).attr('id').substring(4), 10);

        for (var i = 1; i <= $.stars; i++)
        {
            if(i > starnum)
                $('#star' + i).removeClass('color');
            else
            {
                if (!$('#star' + i).hasClass('color'))
                    $('#star' + i).addClass('color');
            }
        }  
    });

    $(document).on('click', '#starsubmit', function (event)
    {
        var i;
        for (i = 1; i <= $.stars; i++)
        {
            if (!$('#star' + i).hasClass('color'))
                break;
        }

        i--;

        ehbridge.bridge('<message>RATING_CLICKED</message><details>'+i+'</details>');

        event.preventDefault();
    });

    $(document).on('click', '#share-opinion-button', function (event)
    {
        var t = $('#shareopinion-text').val();

        if (t.length <= 0)
            $('#shareopinion-text').addClass('textareadplaceholder');
        else
        {
            ehbridge.bridge('<message>SHARE_OPINION_CLICKED</message><details>' + t + '</details>');
            viewChange(44);
        }

        event.preventDefault();
    });
    
    $(document).on('click', '#rating-cancel-click,#rating-cancel-click-feedback', function (event)
    {
        ehbridge.bridge('<message>RATING_CANCEL</message><details>' + i + '</details>');
    });

    $(document).on('click', '.non-clickable', function (event)
    {
        event.preventDefault();
    });

    $(document).on('click', '.button-exit-to-main', function (event)
    {
        viewChange(7);
    });

    $(document).on('click', '#premium-inactive', function (event)
    {
        ehbridge.bridge('<message>MENU_ITEM</message><details>premium</details>');
        event.preventDefault();
    });

    $(document).on('click', '.menu-item', function (event) {

        var href = $(this).attr("href");

        ehbridge.bridge('<message>MENU_ITEM</message><details>' + href + '</details>');

        document.querySelector('.menu-sidebar').classList.remove('visible');

        event.preventDefault();
    });

    try
    {
        $(document).on('click', '.resdatclass', function () {

            var id = $(this).attr('id');

            var thisbtn = $(this), secondbtn;

            var resi = 0;

            switch(id)
            {
                case 'datacenterbtn':

                    secondbtn = $('#residentialbtn');

                    break;

                case 'residentialbtn':

                    secondbtn = $('#datacenterbtn');
                    resi = 1;

                    break;
            }

            var send = "<message>RESIDENTIAL_CHANGED</message><details>" + (resi) + "</details>";
            ehbridge.bridge(send);

            secondbtn.removeClass("active");
            thisbtn.addClass("active");
        });

        $(document).on('click', '.toggle-button', function ()
        {
            $(this).toggleClass('toggle-button-selected');

            var send = "<message>RESIDENTIAL_CHANGED</message><details>" + ($(this).hasClass('toggle-button-selected') ? "1" : "0") + "</details>";

            ehbridge.bridge(send);
        });

        var send = "<message>RESIDENTIAL_SET</message><details></details>";

        ehbridge.bridge(send);

        $.changeView = function(id)
        {
            viewChange(id);
        }

        $.bdate = function (d)
        {
            $("#b-date").html(d);
        }

        $.bversion = function (d)
        {
            $("#b-version").html(d);
        }

        $.set_residential = function(is_residential)
        {
            if (is_residential)
            {
                $('#datacenterbtn').removeClass("active");
                $('#residentialbtn').addClass("active");
            }
            else
            {
                $('#datacenterbtn').addClass("active");
                $('#residentialbtn').removeClass("active");
            }
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

            for (var i = 0; i < objLength(objm[0].list) ; i++) {

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

                    countries.push([iso, full, "qrc:/images/flags/flags/" + img + ".png", true]);

                    //select this ccountry

                    for (var i2 = 0; i2 < objLength(obj.cities) ; i2++) {

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

        $.ClearList = function () { }

        $.SetExpire = function (details) {

            if (details == "hide")
                $('#expire').hide();
            else {
                $('#expire_days').html(details);
                $('#expire').show();
            }
        }

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
        
        $.loginnewoffset = 50;

        $('#oklogin').each(function ()
        {
            $(this).click(function ()
            {
                if ($(this).hasClass('logout-class'))
                {
                    $('#password').val('');
                    $('#email').val('');

                    $('#email,#password').prop('disabled', false);
                    $('#oklogin').html('LOG IN');

                    $(this).removeClass('logout-class');

                    $('#oklogin').removeClass('gray');
                    $('#oklogin').addClass('gold');

                    $('#logininputs').removeClass('logout-form-margin');

                    $('.login-form-logout').hide();
                    $('.login-form-login').show();

                    $('#oklogin').css('bottom', (parseInt($('#oklogin').css('bottom'), 10) + $.loginnewoffset + 20) + 'px');
                    $('#closebuttonlogin').css('bottom', (parseInt($('#closebuttonlogin').css('bottom'), 10) + $.loginnewoffset) + 'px');
                }
                else
                {
                    var email = $('#email').val();
                    var password = $('#password').val();

                    $('#placeholder-style').text('');
                   
                    if(email.length <= 0 || password.length <= 0)
                    {
                        var el_t = 'password';

                        if (email.length <= 0)
                            el_t = 'email';

                        var styleContent = '#' + el_t + ':-moz-placeholder {color: #cb0f0f;} #' + el_t + '::-webkit-input-placeholder {color: #cb0f0f;}';
                        $('#placeholder-style').text(styleContent);

                        return;
                    }
                }

                var email = $('#email').val();
                var password = $('#password').val();

                var send = "<message>SETEMPASS</message><details>{\"idx\":{\"email\":\"" + email + "\", \"password\":\"" + password + "\"}}</details>";

                ehbridge.bridge(send);

                viewChange(7);
            });
        });

        $.SetLogOut = function () {

            $('#email,#password').prop('disabled', true);
            $('#oklogin').html('LOG OUT');

            $('#oklogin').addClass('gray');
            $('#oklogin').removeClass('gold');

            $('.login-form-logout').show();
            $('.login-form-login').hide();

            $('#logininputs').addClass('logout-form-margin');

            $('#oklogin').addClass('logout-class');

            $('#oklogin').css('bottom', (parseInt($('#oklogin').css('bottom'), 10) - $.loginnewoffset - 20) + 'px');
            $('#closebuttonlogin').css('bottom', (parseInt($('#closebuttonlogin').css('bottom'), 10) - $.loginnewoffset) + 'px');
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

        $.EnableDisableLoginButton('true');

        $('#regid1').prepend('<div id="disableregions"></div>');
        $('#couid1').prepend('<div id="disablecountries"></div>');

        $('.headercc:first').prepend('<div id="disablecountriesheader"></div>');
        $('.headercc:last').prepend('<div id="disableregionsheader"></div>');

        $("#country-checkbox-input,#region-checkbox-input").change(function () {

            UpdateUI();

        });

        function UpdateUI() { }

        $.DisableRegions = function () { }

        $.EnableRegions = function () { }

        $.DisableCountries = function () { }

        $.EnableCountries = function () { }

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

        $.DelItem = function DelItem(id) { }

        $.SetPremium = function (val) {

            if (!val)
            {
                $('.premium-hide,#premium-inactive').show();
                $(".free-hide").hide();
            }
            else
            {
                $('.premium-hide,#premium-inactive').hide();
                $(".free-hide").show();
            }
        }

        $.SetPremiumInfo = function (info) {

            var objm = $.parseJSON(info);

            $("#ip_location_pool").text(objm.ip_location_pool);
            $("#ip_location_changes").text(objm.ip_location_changes);
            $("#country_enabled").text(objm.country_enabled);
            $("#city_enabled").text(objm.city_enabled);
            $("#bandwidth").text(objm.bandwidth);
        };

        $.SetMyIp = function (info) {

            var objm = $.parseJSON(info);

            for (var i = 0; i < objm.length; i++) {

                var obj = objm[i].idx;

                $("#location-my-ip").html(obj.countryName + "<br>" + obj.city + (obj.region == null || typeof obj.region === 'undefined' || obj.region.toLowerCase() == "unknown" || obj.region.toLowerCase().length <= 0 ? "" : (" / " + obj.region)));
                $("#image-my-ip").attr("src", "qrc:/img/flags/img/flags/" + obj.countryCodeImg.toLowerCase() + ".png");
            }
        };

        function time_ago(time) {

            switch (typeof time) {
                case 'number':
                    break;
                case 'string':
                    time = +new Date(time);
                    break;
                case 'object':
                    if (time.constructor === Date) time = time.getTime();
                    break;
                default:
                    time = +new Date();
            }
            var time_formats = [
              [60, 'seconds', 1], // 60
              [120, '1 minute ago', '1 minute from now'], // 60*2
              [3600, 'minutes', 60], // 60*60, 60
              [7200, '1 hour ago', '1 hour from now'], // 60*60*2
              [86400, 'hours', 3600], // 60*60*24, 60*60
              [172800, 'Yesterday', 'Tomorrow'], // 60*60*24*2
              [604800, 'days', 86400], // 60*60*24*7, 60*60*24
              [1209600, 'Last week', 'Next week'], // 60*60*24*7*4*2
              [2419200, 'weeks', 604800], // 60*60*24*7*4, 60*60*24*7
              [4838400, 'Last month', 'Next month'], // 60*60*24*7*4*2
              [29030400, 'months', 2419200], // 60*60*24*7*4*12, 60*60*24*7*4
              [58060800, 'Last year', 'Next year'], // 60*60*24*7*4*12*2
              [2903040000, 'years', 29030400], // 60*60*24*7*4*12*100, 60*60*24*7*4*12
              [5806080000, 'Last century', 'Next century'], // 60*60*24*7*4*12*100*2
              [58060800000, 'centuries', 2903040000] // 60*60*24*7*4*12*100*20, 60*60*24*7*4*12*100
            ];
            var seconds = (+new Date() - time) / 1000,
              token = 'ago',
              list_choice = 1;

            if (seconds == 0) {
                return 'Just now'
            }
            if (seconds < 0) {
                seconds = Math.abs(seconds);
                token = 'from now';
                list_choice = 2;
            }
            var i = 0,
              format;
            while (format = time_formats[i++])
                if (seconds < format[0]) {
                    if (typeof format[2] == 'string')
                        return format[list_choice];
                    else
                        return Math.floor(seconds / format[2]) + ' ' + format[1] + ' ' + token;
                }
            return time;
        }

        $.lastChanged = false;

        setInterval(function () { $.updateLastChanged(); }, 5000);

        $.updateLastChanged = function ()
        {
            if($.lastChanged != false)
            {
                var el = $('.time-ago');

                var s_ago = Math.round(+new Date() / 1000) - $.lastChanged;

                if (s_ago < 60)
                    s_ago = "just now";
                else if (s_ago >= 60 && s_ago < 2 * 60)
                    s_ago = "1 minute ago";
                else if (s_ago >= 60 * 2 && s_ago < 60 * 60)
                    s_ago = parseInt(s_ago / 60, 10) + " minutes ago";
                else if (s_ago >= 60 * 60 && s_ago < 60 * 60 * 2)
                    s_ago = "1 hour ago";
                else
                    s_ago = parseInt(s_ago / 60 / 60, 10) + " hours ago";

                el.html("("+s_ago+")");
            }
        };

        $.SetCurrentIp = function (info) {

            var objm = $.parseJSON(info);

            $.lastChanged = Math.round(+new Date() / 1000);

            for (var i = 0; i < objm.length; i++) {

                var obj = objm[i].idx;

                $("#location-current-ip").html(obj.countryName + "<br>" + obj.city + (obj.region == null || typeof obj.region === 'undefined' || obj.region.toLowerCase() == "unknown" || obj.region.toLowerCase().length <= 0 ? "" : (" / " + obj.region)) + "<br /><span class=\"time-ago\"></span>");
                $("#image-current-ip").attr("src", "qrc:/img/flags/img/flags/" + obj.countryCodeImg.toLowerCase() + ".png");
            }

            $.updateLastChanged();
        };

        $.HighLight = function HighLight(id) { }

        $.DataItem = function DataItem(realid, country, city, region, imgurl, addid, highlight) { }


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

            $('.upgrade_to_premium,.upgrade_to_premium_').click(function () {

                ehbridge.bridge('<message>OPENPREMIUM</message><details></details>');
            });

            $('.upgrade_to_premium_free,.upgrade_to_premium_free_').click(function () {

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

            $.AddItems = function AddItems(items) { }
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

        $.AddRegion = function (region, checked) { };

        $.REMOVEALLREGIONSFORISO = function (iso) { }

        $.RemoveRegion = function (region, always) { };

        $.AddCountry = function (country, checked) { };

        $.RemoveCountry = function (country, always) { };

        $.RefreshRegionsCountries = function () { }

        $.AddIP = function (info) { }

        $.RemoveIP = function (info) { }

        $.hideiplist = false;

        $.SetIpListVisibility = function SetIpListVisibility(setv) {

            if (!$.EnableSwitch) $('#iplistswitch').prop('checked', false);

            if ($('#iplistswitch').is(":checked") && !$.hideiplist) {

                $.IPvis = true;
                $('.list-visible').show();
                $('.list-invisible').hide();

            } else {

                $.IPvis = false;
                $('.list-visible').hide();
                $('.list-invisible').show();
            }
        }

        $('#iplistswitch').change(function () {

            var ret = $('#iplistswitch').is(":checked") ? "1" : "0";

            $.SetIpListVisibility();

            ehbridge.bridge('<message>IPLISTVISIBILITY</message><details>' + (ret) + '</details>');
        });

        $.SetIpListVisibility();

        ehbridge.bridge('<message>LOADED</message><details></details>');
    }
    catch (e)
    {
        //alert(e.stack);
    }
    
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

                if (country) {
                    for (var i = 0; i < $.country_city_list.length; i++) {
                        if (val == $.country_city_list[i][0]) {
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
                    ehbridge.bridge("<message>CITY_CHANGED</message><details>" + val + "</details>");

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

    if ($.fn.perfectScrollbar) {
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

    for (var i = 0; i < countries.length; i++) {
        if (countries[i][3]) {
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

    for (var i = 0; i < cities.length; i++) {
        if (cities[i][1]) {
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

    $(document).on('click', "#next_nearby", function ()
    {
        ehbridge.bridge("<message>NEXT_NEARBY</message><details></details>");
    });

    $(".infolink").hover(function ()
    {
        $(".tooltip").show();

    },
    function ()
    {
        $(".tooltip").hide();
    });

    $("#country-select").chosenImage();
    $("#city-select").chosenImage();


    checkDOMChange();
});