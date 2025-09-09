if (window.NodeList && !NodeList.prototype.forEach) {
    NodeList.prototype.forEach = Array.prototype.forEach;
}

'use strict';

var switcherTypes = document.querySelectorAll('.type-switcher .type');
switcherTypes.forEach(function (type) {
    type.addEventListener('click', function (e) {
        switcherTypes.forEach(function (type) {
            type.classList.remove('active');
        });
        type.classList.add('active');
    });
});

var hams = document.querySelectorAll('.menu-bar .ham');
var menu = document.querySelector('.menu-sidebar');
var menuExit = document.querySelector('.menu-sidebar .icon--exit');

hams.forEach(function (ham) {
    ham.addEventListener('click', function (e) {
        menu.classList.add('visible');
        menu.classList.add('force-show');
    });
});

menuExit.addEventListener('click', function (e) {
    menu.classList.remove('visible');
});

var views = document.querySelectorAll('body div.view');
var flags = document.querySelectorAll('body img.icon--flag');

function viewChange(id) {
    if (!id) id = 13;
    views.forEach(function (view) {
        view.classList.remove('visible');
    });
    var view = document.getElementById(id);
    if (view !== null) {
        view.classList.add('visible');
    } else document.getElementById(13).classList.add('visible');
}

function flagChange(iso) {
    if (!iso) iso = 'us';
    flags.forEach(function (flag) {
        flag.src = 'qrc:/img/flags/img/flags/' + iso + '.png';
    });
}