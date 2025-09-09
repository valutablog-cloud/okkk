//
//  ISO.cpp
//  Tuxler
//
//  Created by Jaroslaw Lazar on 17.10.2013.
//  Copyright (c) 2013 JATAR. All rights reserved.
//

#include "translator.h"


QString Translator::TryGetFullRegion(QString &regionisoutf8, QString &countryisoutf8){

    QString ret = "";

    QString regiso (regionisoutf8);
    QString ciso (countryisoutf8);

    for(int i = 0; i < lstreg.size(); i++){

        if(regiso.toLower() == lstreg[i].toLower() && i > 1 && ciso.toLower() == lstreg[i-1].toLower()){

            ret = lstreg[i-2];
            break;

        }
    }

    return (ret);
}


QList<Region> Translator::TryGetRegions(QString &countryisoutf8){

    QList<Region> ret;

    QString ciso (countryisoutf8);

    for(int i = 1; i < lstreg.size(); i+=3){

        if(i+1 > lstreg.size()-1) break;

        if(ciso.toLower() == lstreg[i].toLower()){

            Region reg;

            reg.regioniso = (lstreg[i+1]);
            reg.regionfull = (lstreg[i-1]);

            ret.append(reg);
        }
    }

    return ret;
}




Translator::Translator(){

    lstreg.append("Alberta");
    lstreg.append("CA");
    lstreg.append("BC");

    lstreg.append("British Columbia");
    lstreg.append("CA");
    lstreg.append("MB");

    lstreg.append("Manitoba");
    lstreg.append("CA");
    lstreg.append("NB");

    lstreg.append("New Brunswick");
    lstreg.append("CA");
    lstreg.append("NL");

    lstreg.append("Newfoundland");
    lstreg.append("CA");
    lstreg.append("NS");

    lstreg.append("Nova Scotia");
    lstreg.append("CA");
    lstreg.append("NU");

    lstreg.append("Nunavut");
    lstreg.append("CA");
    lstreg.append("ON");

    lstreg.append("Ontario");
    lstreg.append("CA");
    lstreg.append("PE");

    lstreg.append("Prince Edward Island");
    lstreg.append("CA");
    lstreg.append("QC");

    lstreg.append("Quebec");
    lstreg.append("CA");
    lstreg.append("SK");

    lstreg.append("Saskatchewan");
    lstreg.append("CA");
    lstreg.append("NT");

    lstreg.append("Northwest Territories");
    lstreg.append("CA");
    lstreg.append("YT");

    lstreg.append("Yukon Territory");
    lstreg.append("US");
    lstreg.append("AA");

    lstreg.append("Armed Forces Americas");
    lstreg.append("US");
    lstreg.append("AE");

    lstreg.append("Armed Forces Europe Middle East & Canada");
    lstreg.append("US");
    lstreg.append("AK");

    lstreg.append("Alaska");
    lstreg.append("US");
    lstreg.append("AL");

    lstreg.append("Alabama");
    lstreg.append("US");
    lstreg.append("AP");

    lstreg.append("Armed Forces Pacific");
    lstreg.append("US");
    lstreg.append("AR");

    lstreg.append("Arkansas");
    lstreg.append("US");
    lstreg.append("AS");

    lstreg.append("American Samoa");
    lstreg.append("US");
    lstreg.append("AZ");

    lstreg.append("Arizona");
    lstreg.append("US");
    lstreg.append("CA");

    lstreg.append("California");
    lstreg.append("US");
    lstreg.append("CO");

    lstreg.append("Colorado");
    lstreg.append("US");
    lstreg.append("CT");

    lstreg.append("Connecticut");
    lstreg.append("US");
    lstreg.append("DC");

    lstreg.append("District of Columbia");
    lstreg.append("US");
    lstreg.append("DE");

    lstreg.append("Delaware");
    lstreg.append("US");
    lstreg.append("FL");

    lstreg.append("Florida");
    lstreg.append("US");
    lstreg.append("FM");

    lstreg.append("Federated States of Micronesia");
    lstreg.append("US");
    lstreg.append("GA");

    lstreg.append("Georgia");
    lstreg.append("US");
    lstreg.append("GU");

    lstreg.append("Guam");
    lstreg.append("US");
    lstreg.append("HI");

    lstreg.append("Hawaii");
    lstreg.append("US");
    lstreg.append("IA");

    lstreg.append("Iowa");
    lstreg.append("US");
    lstreg.append("ID");

    lstreg.append("Idaho");
    lstreg.append("US");
    lstreg.append("IL");

    lstreg.append("Illinois");
    lstreg.append("US");
    lstreg.append("IN");

    lstreg.append("Indiana");
    lstreg.append("US");
    lstreg.append("KS");

    lstreg.append("Kansas");
    lstreg.append("US");
    lstreg.append("KY");

    lstreg.append("Kentucky");
    lstreg.append("US");
    lstreg.append("LA");

    lstreg.append("Louisiana");
    lstreg.append("US");
    lstreg.append("MA");

    lstreg.append("Massachusetts");
    lstreg.append("US");
    lstreg.append("MD");

    lstreg.append("Maryland");
    lstreg.append("US");
    lstreg.append("ME");

    lstreg.append("Maine");
    lstreg.append("US");
    lstreg.append("MH");

    lstreg.append("Marshall Islands");
    lstreg.append("US");
    lstreg.append("MI");

    lstreg.append("Michigan");
    lstreg.append("US");
    lstreg.append("MN");

    lstreg.append("Minnesota");
    lstreg.append("US");
    lstreg.append("MO");

    lstreg.append("Missouri");
    lstreg.append("US");
    lstreg.append("MP");

    lstreg.append("Northern Mariana Islands");
    lstreg.append("US");
    lstreg.append("MS");

    lstreg.append("Mississippi");
    lstreg.append("US");
    lstreg.append("MT");

    lstreg.append("Montana");
    lstreg.append("US");
    lstreg.append("NC");

    lstreg.append("North Carolina");
    lstreg.append("US");
    lstreg.append("ND");

    lstreg.append("North Dakota");
    lstreg.append("US");
    lstreg.append("NE");

    lstreg.append("Nebraska");
    lstreg.append("US");
    lstreg.append("NH");

    lstreg.append("New Hampshire");
    lstreg.append("US");
    lstreg.append("NJ");

    lstreg.append("New Jersey");
    lstreg.append("US");
    lstreg.append("NM");

    lstreg.append("New Mexico");
    lstreg.append("US");
    lstreg.append("NV");

    lstreg.append("Nevada");
    lstreg.append("US");
    lstreg.append("NY");

    lstreg.append("New York");
    lstreg.append("US");
    lstreg.append("OH");

    lstreg.append("Ohio");
    lstreg.append("US");
    lstreg.append("OK");

    lstreg.append("Oklahoma");
    lstreg.append("US");
    lstreg.append("OR");

    lstreg.append("Oregon");
    lstreg.append("US");
    lstreg.append("PA");

    lstreg.append("Pennsylvania");
    lstreg.append("US");
    lstreg.append("PR");

    lstreg.append("Puerto Rico");
    lstreg.append("US");
    lstreg.append("PW");

    lstreg.append("Palau");
    lstreg.append("US");
    lstreg.append("RI");

    lstreg.append("Rhode Island");
    lstreg.append("US");
    lstreg.append("SC");

    lstreg.append("South Carolina");
    lstreg.append("US");
    lstreg.append("SD");

    lstreg.append("South Dakota");
    lstreg.append("US");
    lstreg.append("TN");

    lstreg.append("Tennessee");
    lstreg.append("US");
    lstreg.append("TX");

    lstreg.append("Texas");
    lstreg.append("US");
    lstreg.append("UT");

    lstreg.append("Utah");
    lstreg.append("US");
    lstreg.append("VA");

    lstreg.append("Virginia");
    lstreg.append("US");
    lstreg.append("VI");

    lstreg.append("Virgin Islands");
    lstreg.append("US");
    lstreg.append("VT");

    lstreg.append("Vermont");
    lstreg.append("US");
    lstreg.append("WA");

    lstreg.append("Washington");
    lstreg.append("US");
    lstreg.append("WV");

    lstreg.append("West Virginia");
    lstreg.append("US");
    lstreg.append("WI");

    lstreg.append("Wisconsin");
    lstreg.append("US");
    lstreg.append("WY");

    lstreg.append("Wyoming");
    lstreg.append("AD");
    lstreg.append("02");

    lstreg.append("Canillo");
    lstreg.append("AD");
    lstreg.append("03");

    lstreg.append("Encamp");
    lstreg.append("AD");
    lstreg.append("04");

    lstreg.append("La Massana");
    lstreg.append("AD");
    lstreg.append("05");

    lstreg.append("Ordino");
    lstreg.append("AD");
    lstreg.append("06");

    lstreg.append("Sant Julia de Loria");
    lstreg.append("AD");
    lstreg.append("07");

    lstreg.append("Andorra la Vella");
    lstreg.append("AD");
    lstreg.append("08");

    lstreg.append("Escaldes-Engordany");
    lstreg.append("AE");
    lstreg.append("01");

    lstreg.append("Abu Dhabi");
    lstreg.append("AE");
    lstreg.append("02");

    lstreg.append("Ajman");
    lstreg.append("AE");
    lstreg.append("03");

    lstreg.append("Dubai");
    lstreg.append("AE");
    lstreg.append("04");

    lstreg.append("Fujairah");
    lstreg.append("AE");
    lstreg.append("05");

    lstreg.append("Ras Al Khaimah");
    lstreg.append("AE");
    lstreg.append("06");

    lstreg.append("Sharjah");
    lstreg.append("AE");
    lstreg.append("07");

    lstreg.append("Umm Al Quwain");
    lstreg.append("AF");
    lstreg.append("01");

    lstreg.append("Badakhshan");
    lstreg.append("AF");
    lstreg.append("02");

    lstreg.append("Badghis");
    lstreg.append("AF");
    lstreg.append("03");

    lstreg.append("Baghlan");
    lstreg.append("AF");
    lstreg.append("05");

    lstreg.append("Bamian");
    lstreg.append("AF");
    lstreg.append("06");

    lstreg.append("Farah");
    lstreg.append("AF");
    lstreg.append("07");

    lstreg.append("Faryab");
    lstreg.append("AF");
    lstreg.append("08");

    lstreg.append("Ghazni");
    lstreg.append("AF");
    lstreg.append("09");

    lstreg.append("Ghowr");
    lstreg.append("AF");
    lstreg.append("10");

    lstreg.append("Helmand");
    lstreg.append("AF");
    lstreg.append("11");

    lstreg.append("Herat");
    lstreg.append("AF");
    lstreg.append("13");

    lstreg.append("Kabol");
    lstreg.append("AF");
    lstreg.append("14");

    lstreg.append("Kapisa");
    lstreg.append("AF");
    lstreg.append("17");

    lstreg.append("Lowgar");
    lstreg.append("AF");
    lstreg.append("18");

    lstreg.append("Nangarhar");
    lstreg.append("AF");
    lstreg.append("19");

    lstreg.append("Nimruz");
    lstreg.append("AF");
    lstreg.append("23");

    lstreg.append("Kandahar");
    lstreg.append("AF");
    lstreg.append("24");

    lstreg.append("Kondoz");
    lstreg.append("AF");
    lstreg.append("26");

    lstreg.append("Takhar");
    lstreg.append("AF");
    lstreg.append("27");

    lstreg.append("Vardak");
    lstreg.append("AF");
    lstreg.append("28");

    lstreg.append("Zabol");
    lstreg.append("AF");
    lstreg.append("29");

    lstreg.append("Paktika");
    lstreg.append("AF");
    lstreg.append("30");

    lstreg.append("Balkh");
    lstreg.append("AF");
    lstreg.append("31");

    lstreg.append("Jowzjan");
    lstreg.append("AF");
    lstreg.append("32");

    lstreg.append("Samangan");
    lstreg.append("AF");
    lstreg.append("33");

    lstreg.append("Sar-e Pol");
    lstreg.append("AF");
    lstreg.append("34");

    lstreg.append("Konar");
    lstreg.append("AF");
    lstreg.append("35");

    lstreg.append("Laghman");
    lstreg.append("AF");
    lstreg.append("36");

    lstreg.append("Paktia");
    lstreg.append("AF");
    lstreg.append("37");

    lstreg.append("Khowst");
    lstreg.append("AF");
    lstreg.append("38");

    lstreg.append("Nurestan");
    lstreg.append("AF");
    lstreg.append("39");

    lstreg.append("Oruzgan");
    lstreg.append("AF");
    lstreg.append("40");

    lstreg.append("Parvan");
    lstreg.append("AF");
    lstreg.append("41");

    lstreg.append("Daykondi");
    lstreg.append("AF");
    lstreg.append("42");

    lstreg.append("Panjshir");
    lstreg.append("AG");
    lstreg.append("01");

    lstreg.append("Barbuda");
    lstreg.append("AG");
    lstreg.append("03");

    lstreg.append("Saint George");
    lstreg.append("AG");
    lstreg.append("04");

    lstreg.append("Saint John");
    lstreg.append("AG");
    lstreg.append("05");

    lstreg.append("Saint Mary");
    lstreg.append("AG");
    lstreg.append("06");

    lstreg.append("Saint Paul");
    lstreg.append("AG");
    lstreg.append("07");

    lstreg.append("Saint Peter");
    lstreg.append("AG");
    lstreg.append("08");

    lstreg.append("Saint Philip");
    lstreg.append("AG");
    lstreg.append("09");

    lstreg.append("Redonda");
    lstreg.append("AL");
    lstreg.append("40");

    lstreg.append("Berat");
    lstreg.append("AL");
    lstreg.append("41");

    lstreg.append("Diber");
    lstreg.append("AL");
    lstreg.append("42");

    lstreg.append("Durres");
    lstreg.append("AL");
    lstreg.append("43");

    lstreg.append("Elbasan");
    lstreg.append("AL");
    lstreg.append("44");

    lstreg.append("Fier");
    lstreg.append("AL");
    lstreg.append("45");

    lstreg.append("Gjirokaster");
    lstreg.append("AL");
    lstreg.append("46");

    lstreg.append("Korce");
    lstreg.append("AL");
    lstreg.append("47");

    lstreg.append("Kukes");
    lstreg.append("AL");
    lstreg.append("48");

    lstreg.append("Lezhe");
    lstreg.append("AL");
    lstreg.append("49");

    lstreg.append("Shkoder");
    lstreg.append("AL");
    lstreg.append("50");

    lstreg.append("Tirane");
    lstreg.append("AL");
    lstreg.append("51");

    lstreg.append("Vlore");
    lstreg.append("AM");
    lstreg.append("01");

    lstreg.append("Aragatsotn");
    lstreg.append("AM");
    lstreg.append("02");

    lstreg.append("Ararat");
    lstreg.append("AM");
    lstreg.append("03");

    lstreg.append("Armavir");
    lstreg.append("AM");
    lstreg.append("04");

    lstreg.append("Geghark'unik'");
    lstreg.append("AM");
    lstreg.append("05");

    lstreg.append("Kotayk'");
    lstreg.append("AM");
    lstreg.append("06");

    lstreg.append("Lorri");
    lstreg.append("AM");
    lstreg.append("07");

    lstreg.append("Shirak");
    lstreg.append("AM");
    lstreg.append("08");

    lstreg.append("Syunik'");
    lstreg.append("AM");
    lstreg.append("09");

    lstreg.append("Tavush");
    lstreg.append("AM");
    lstreg.append("10");

    lstreg.append("Vayots' Dzor");
    lstreg.append("AM");
    lstreg.append("11");

    lstreg.append("Yerevan");
    lstreg.append("AO");
    lstreg.append("01");

    lstreg.append("Benguela");
    lstreg.append("AO");
    lstreg.append("02");

    lstreg.append("Bie");
    lstreg.append("AO");
    lstreg.append("03");

    lstreg.append("Cabinda");
    lstreg.append("AO");
    lstreg.append("04");

    lstreg.append("Cuando Cubango");
    lstreg.append("AO");
    lstreg.append("05");

    lstreg.append("Cuanza Norte");
    lstreg.append("AO");
    lstreg.append("06");

    lstreg.append("Cuanza Sul");
    lstreg.append("AO");
    lstreg.append("07");

    lstreg.append("Cunene");
    lstreg.append("AO");
    lstreg.append("08");

    lstreg.append("Huambo");
    lstreg.append("AO");
    lstreg.append("09");

    lstreg.append("Huila");
    lstreg.append("AO");
    lstreg.append("12");

    lstreg.append("Malanje");
    lstreg.append("AO");
    lstreg.append("13");

    lstreg.append("Namibe");
    lstreg.append("AO");
    lstreg.append("14");

    lstreg.append("Moxico");
    lstreg.append("AO");
    lstreg.append("15");

    lstreg.append("Uige");
    lstreg.append("AO");
    lstreg.append("16");

    lstreg.append("Zaire");
    lstreg.append("AO");
    lstreg.append("17");

    lstreg.append("Lunda Norte");
    lstreg.append("AO");
    lstreg.append("18");

    lstreg.append("Lunda Sul");
    lstreg.append("AO");
    lstreg.append("19");

    lstreg.append("Bengo");
    lstreg.append("AO");
    lstreg.append("20");

    lstreg.append("Luanda");
    lstreg.append("AR");
    lstreg.append("01");

    lstreg.append("Buenos Aires");
    lstreg.append("AR");
    lstreg.append("02");

    lstreg.append("Catamarca");
    lstreg.append("AR");
    lstreg.append("03");

    lstreg.append("Chaco");
    lstreg.append("AR");
    lstreg.append("04");

    lstreg.append("Chubut");
    lstreg.append("AR");
    lstreg.append("05");

    lstreg.append("Cordoba");
    lstreg.append("AR");
    lstreg.append("06");

    lstreg.append("Corrientes");
    lstreg.append("AR");
    lstreg.append("07");

    lstreg.append("Distrito Federal");
    lstreg.append("AR");
    lstreg.append("08");

    lstreg.append("Entre Rios");
    lstreg.append("AR");
    lstreg.append("09");

    lstreg.append("Formosa");
    lstreg.append("AR");
    lstreg.append("10");

    lstreg.append("Jujuy");
    lstreg.append("AR");
    lstreg.append("11");

    lstreg.append("La Pampa");
    lstreg.append("AR");
    lstreg.append("12");

    lstreg.append("La Rioja");
    lstreg.append("AR");
    lstreg.append("13");

    lstreg.append("Mendoza");
    lstreg.append("AR");
    lstreg.append("14");

    lstreg.append("Misiones");
    lstreg.append("AR");
    lstreg.append("15");

    lstreg.append("Neuquen");
    lstreg.append("AR");
    lstreg.append("16");

    lstreg.append("Rio Negro");
    lstreg.append("AR");
    lstreg.append("17");

    lstreg.append("Salta");
    lstreg.append("AR");
    lstreg.append("18");

    lstreg.append("San Juan");
    lstreg.append("AR");
    lstreg.append("19");

    lstreg.append("San Luis");
    lstreg.append("AR");
    lstreg.append("20");

    lstreg.append("Santa Cruz");
    lstreg.append("AR");
    lstreg.append("21");

    lstreg.append("Santa Fe");
    lstreg.append("AR");
    lstreg.append("22");

    lstreg.append("Santiago del Estero");
    lstreg.append("AR");
    lstreg.append("23");

    lstreg.append("Tierra del Fuego");
    lstreg.append("AR");
    lstreg.append("24");

    lstreg.append("Tucuman");
    lstreg.append("AT");
    lstreg.append("01");

    lstreg.append("Burgenland");
    lstreg.append("AT");
    lstreg.append("02");

    lstreg.append("Karnten");
    lstreg.append("AT");
    lstreg.append("03");

    lstreg.append("Niederosterreich");
    lstreg.append("AT");
    lstreg.append("04");

    lstreg.append("Oberosterreich");
    lstreg.append("AT");
    lstreg.append("05");

    lstreg.append("Salzburg");
    lstreg.append("AT");
    lstreg.append("06");

    lstreg.append("Steiermark");
    lstreg.append("AT");
    lstreg.append("07");

    lstreg.append("Tirol");
    lstreg.append("AT");
    lstreg.append("08");

    lstreg.append("Vorarlberg");
    lstreg.append("AT");
    lstreg.append("09");

    lstreg.append("Wien");
    lstreg.append("AU");
    lstreg.append("01");

    lstreg.append("Australian Capital Territory");
    lstreg.append("AU");
    lstreg.append("02");

    lstreg.append("New South Wales");
    lstreg.append("AU");
    lstreg.append("03");

    lstreg.append("Northern Territory");
    lstreg.append("AU");
    lstreg.append("04");

    lstreg.append("Queensland");
    lstreg.append("AU");
    lstreg.append("05");

    lstreg.append("South Australia");
    lstreg.append("AU");
    lstreg.append("06");

    lstreg.append("Tasmania");
    lstreg.append("AU");
    lstreg.append("07");

    lstreg.append("Victoria");
    lstreg.append("AU");
    lstreg.append("08");

    lstreg.append("Western Australia");
    lstreg.append("AZ");
    lstreg.append("01");

    lstreg.append("Abseron");
    lstreg.append("AZ");
    lstreg.append("02");

    lstreg.append("Agcabadi");
    lstreg.append("AZ");
    lstreg.append("03");

    lstreg.append("Agdam");
    lstreg.append("AZ");
    lstreg.append("04");

    lstreg.append("Agdas");
    lstreg.append("AZ");
    lstreg.append("05");

    lstreg.append("Agstafa");
    lstreg.append("AZ");
    lstreg.append("06");

    lstreg.append("Agsu");
    lstreg.append("AZ");
    lstreg.append("07");

    lstreg.append("Ali Bayramli");
    lstreg.append("AZ");
    lstreg.append("08");

    lstreg.append("Astara");
    lstreg.append("AZ");
    lstreg.append("09");

    lstreg.append("Baki");
    lstreg.append("AZ");
    lstreg.append("10");

    lstreg.append("Balakan");
    lstreg.append("AZ");
    lstreg.append("11");

    lstreg.append("Barda");
    lstreg.append("AZ");
    lstreg.append("12");

    lstreg.append("Beylaqan");
    lstreg.append("AZ");
    lstreg.append("13");

    lstreg.append("Bilasuvar");
    lstreg.append("AZ");
    lstreg.append("14");

    lstreg.append("Cabrayil");
    lstreg.append("AZ");
    lstreg.append("15");

    lstreg.append("Calilabad");
    lstreg.append("AZ");
    lstreg.append("16");

    lstreg.append("Daskasan");
    lstreg.append("AZ");
    lstreg.append("17");

    lstreg.append("Davaci");
    lstreg.append("AZ");
    lstreg.append("18");

    lstreg.append("Fuzuli");
    lstreg.append("AZ");
    lstreg.append("19");

    lstreg.append("Gadabay");
    lstreg.append("AZ");
    lstreg.append("20");

    lstreg.append("Ganca");
    lstreg.append("AZ");
    lstreg.append("21");

    lstreg.append("Goranboy");
    lstreg.append("AZ");
    lstreg.append("22");

    lstreg.append("Goycay");
    lstreg.append("AZ");
    lstreg.append("23");

    lstreg.append("Haciqabul");
    lstreg.append("AZ");
    lstreg.append("24");

    lstreg.append("Imisli");
    lstreg.append("AZ");
    lstreg.append("25");

    lstreg.append("Ismayilli");
    lstreg.append("AZ");
    lstreg.append("26");

    lstreg.append("Kalbacar");
    lstreg.append("AZ");
    lstreg.append("27");

    lstreg.append("Kurdamir");
    lstreg.append("AZ");
    lstreg.append("28");

    lstreg.append("Lacin");
    lstreg.append("AZ");
    lstreg.append("29");

    lstreg.append("Lankaran");
    lstreg.append("AZ");
    lstreg.append("30");

    lstreg.append("Lankaran");
    lstreg.append("AZ");
    lstreg.append("31");

    lstreg.append("Lerik");
    lstreg.append("AZ");
    lstreg.append("32");

    lstreg.append("Masalli");
    lstreg.append("AZ");
    lstreg.append("33");

    lstreg.append("Mingacevir");
    lstreg.append("AZ");
    lstreg.append("34");

    lstreg.append("Naftalan");
    lstreg.append("AZ");
    lstreg.append("35");

    lstreg.append("Naxcivan");
    lstreg.append("AZ");
    lstreg.append("36");

    lstreg.append("Neftcala");
    lstreg.append("AZ");
    lstreg.append("37");

    lstreg.append("Oguz");
    lstreg.append("AZ");
    lstreg.append("38");

    lstreg.append("Qabala");
    lstreg.append("AZ");
    lstreg.append("39");

    lstreg.append("Qax");
    lstreg.append("AZ");
    lstreg.append("40");

    lstreg.append("Qazax");
    lstreg.append("AZ");
    lstreg.append("41");

    lstreg.append("Qobustan");
    lstreg.append("AZ");
    lstreg.append("42");

    lstreg.append("Quba");
    lstreg.append("AZ");
    lstreg.append("43");

    lstreg.append("Qubadli");
    lstreg.append("AZ");
    lstreg.append("44");

    lstreg.append("Qusar");
    lstreg.append("AZ");
    lstreg.append("45");

    lstreg.append("Saatli");
    lstreg.append("AZ");
    lstreg.append("46");

    lstreg.append("Sabirabad");
    lstreg.append("AZ");
    lstreg.append("47");

    lstreg.append("Saki");
    lstreg.append("AZ");
    lstreg.append("48");

    lstreg.append("Saki");
    lstreg.append("AZ");
    lstreg.append("49");

    lstreg.append("Salyan");
    lstreg.append("AZ");
    lstreg.append("50");

    lstreg.append("Samaxi");
    lstreg.append("AZ");
    lstreg.append("51");

    lstreg.append("Samkir");
    lstreg.append("AZ");
    lstreg.append("52");

    lstreg.append("Samux");
    lstreg.append("AZ");
    lstreg.append("53");

    lstreg.append("Siyazan");
    lstreg.append("AZ");
    lstreg.append("54");

    lstreg.append("Sumqayit");
    lstreg.append("AZ");
    lstreg.append("55");

    lstreg.append("Susa");
    lstreg.append("AZ");
    lstreg.append("56");

    lstreg.append("Susa");
    lstreg.append("AZ");
    lstreg.append("57");

    lstreg.append("Tartar");
    lstreg.append("AZ");
    lstreg.append("58");

    lstreg.append("Tovuz");
    lstreg.append("AZ");
    lstreg.append("59");

    lstreg.append("Ucar");
    lstreg.append("AZ");
    lstreg.append("60");

    lstreg.append("Xacmaz");
    lstreg.append("AZ");
    lstreg.append("61");

    lstreg.append("Xankandi");
    lstreg.append("AZ");
    lstreg.append("62");

    lstreg.append("Xanlar");
    lstreg.append("AZ");
    lstreg.append("63");

    lstreg.append("Xizi");
    lstreg.append("AZ");
    lstreg.append("64");

    lstreg.append("Xocali");
    lstreg.append("AZ");
    lstreg.append("65");

    lstreg.append("Xocavand");
    lstreg.append("AZ");
    lstreg.append("66");

    lstreg.append("Yardimli");
    lstreg.append("AZ");
    lstreg.append("67");

    lstreg.append("Yevlax");
    lstreg.append("AZ");
    lstreg.append("68");

    lstreg.append("Yevlax");
    lstreg.append("AZ");
    lstreg.append("69");

    lstreg.append("Zangilan");
    lstreg.append("AZ");
    lstreg.append("70");

    lstreg.append("Zaqatala");
    lstreg.append("AZ");
    lstreg.append("71");

    lstreg.append("Zardab");
    lstreg.append("BA");
    lstreg.append("01");

    lstreg.append("Federation of Bosnia and Herzegovina");
    lstreg.append("BA");
    lstreg.append("02");

    lstreg.append("Republika Srpska");
    lstreg.append("BB");
    lstreg.append("01");

    lstreg.append("Christ Church");
    lstreg.append("BB");
    lstreg.append("02");

    lstreg.append("Saint Andrew");
    lstreg.append("BB");
    lstreg.append("03");

    lstreg.append("Saint George");
    lstreg.append("BB");
    lstreg.append("04");

    lstreg.append("Saint James");
    lstreg.append("BB");
    lstreg.append("05");

    lstreg.append("Saint John");
    lstreg.append("BB");
    lstreg.append("06");

    lstreg.append("Saint Joseph");
    lstreg.append("BB");
    lstreg.append("07");

    lstreg.append("Saint Lucy");
    lstreg.append("BB");
    lstreg.append("08");

    lstreg.append("Saint Michael");
    lstreg.append("BB");
    lstreg.append("09");

    lstreg.append("Saint Peter");
    lstreg.append("BB");
    lstreg.append("10");

    lstreg.append("Saint Philip");
    lstreg.append("BB");
    lstreg.append("11");

    lstreg.append("Saint Thomas");
    lstreg.append("BD");
    lstreg.append("81");

    lstreg.append("Dhaka");
    lstreg.append("BD");
    lstreg.append("82");

    lstreg.append("Khulna");
    lstreg.append("BD");
    lstreg.append("83");

    lstreg.append("Rajshahi");
    lstreg.append("BD");
    lstreg.append("84");

    lstreg.append("Chittagong");
    lstreg.append("BD");
    lstreg.append("85");

    lstreg.append("Barisal");
    lstreg.append("BD");
    lstreg.append("86");

    lstreg.append("Sylhet");
    lstreg.append("BE");
    lstreg.append("01");

    lstreg.append("Antwerpen");
    lstreg.append("BE");
    lstreg.append("03");

    lstreg.append("Hainaut");
    lstreg.append("BE");
    lstreg.append("04");

    lstreg.append("Liege");
    lstreg.append("BE");
    lstreg.append("05");

    lstreg.append("Limburg");
    lstreg.append("BE");
    lstreg.append("06");

    lstreg.append("Luxembourg");
    lstreg.append("BE");
    lstreg.append("07");

    lstreg.append("Namur");
    lstreg.append("BE");
    lstreg.append("08");

    lstreg.append("Oost-Vlaanderen");
    lstreg.append("BE");
    lstreg.append("09");

    lstreg.append("West-Vlaanderen");
    lstreg.append("BE");
    lstreg.append("10");

    lstreg.append("Brabant Wallon");
    lstreg.append("BE");
    lstreg.append("11");

    lstreg.append("Brussels Hoofdstedelijk Gewest");
    lstreg.append("BE");
    lstreg.append("12");

    lstreg.append("Vlaams-Brabant");
    lstreg.append("BF");
    lstreg.append("15");

    lstreg.append("Bam");
    lstreg.append("BF");
    lstreg.append("19");

    lstreg.append("Boulkiemde");
    lstreg.append("BF");
    lstreg.append("20");

    lstreg.append("Ganzourgou");
    lstreg.append("BF");
    lstreg.append("21");

    lstreg.append("Gnagna");
    lstreg.append("BF");
    lstreg.append("28");

    lstreg.append("Kouritenga");
    lstreg.append("BF");
    lstreg.append("33");

    lstreg.append("Oudalan");
    lstreg.append("BF");
    lstreg.append("34");

    lstreg.append("Passore");
    lstreg.append("BF");
    lstreg.append("36");

    lstreg.append("Sanguie");
    lstreg.append("BF");
    lstreg.append("40");

    lstreg.append("Soum");
    lstreg.append("BF");
    lstreg.append("42");

    lstreg.append("Tapoa");
    lstreg.append("BF");
    lstreg.append("44");

    lstreg.append("Zoundweogo");
    lstreg.append("BF");
    lstreg.append("45");

    lstreg.append("Bale");
    lstreg.append("BF");
    lstreg.append("46");

    lstreg.append("Banwa");
    lstreg.append("BF");
    lstreg.append("47");

    lstreg.append("Bazega");
    lstreg.append("BF");
    lstreg.append("48");

    lstreg.append("Bougouriba");
    lstreg.append("BF");
    lstreg.append("49");

    lstreg.append("Boulgou");
    lstreg.append("BF");
    lstreg.append("50");

    lstreg.append("Gourma");
    lstreg.append("BF");
    lstreg.append("51");

    lstreg.append("Houet");
    lstreg.append("BF");
    lstreg.append("52");

    lstreg.append("Ioba");
    lstreg.append("BF");
    lstreg.append("53");

    lstreg.append("Kadiogo");
    lstreg.append("BF");
    lstreg.append("54");

    lstreg.append("Kenedougou");
    lstreg.append("BF");
    lstreg.append("55");

    lstreg.append("Komoe");
    lstreg.append("BF");
    lstreg.append("56");

    lstreg.append("Komondjari");
    lstreg.append("BF");
    lstreg.append("57");

    lstreg.append("Kompienga");
    lstreg.append("BF");
    lstreg.append("58");

    lstreg.append("Kossi");
    lstreg.append("BF");
    lstreg.append("59");

    lstreg.append("Koulpelogo");
    lstreg.append("BF");
    lstreg.append("60");

    lstreg.append("Kourweogo");
    lstreg.append("BF");
    lstreg.append("61");

    lstreg.append("Leraba");
    lstreg.append("BF");
    lstreg.append("62");

    lstreg.append("Loroum");
    lstreg.append("BF");
    lstreg.append("63");

    lstreg.append("Mouhoun");
    lstreg.append("BF");
    lstreg.append("64");

    lstreg.append("Namentenga");
    lstreg.append("BF");
    lstreg.append("65");

    lstreg.append("Naouri");
    lstreg.append("BF");
    lstreg.append("66");

    lstreg.append("Nayala");
    lstreg.append("BF");
    lstreg.append("67");

    lstreg.append("Noumbiel");
    lstreg.append("BF");
    lstreg.append("68");

    lstreg.append("Oubritenga");
    lstreg.append("BF");
    lstreg.append("69");

    lstreg.append("Poni");
    lstreg.append("BF");
    lstreg.append("70");

    lstreg.append("Sanmatenga");
    lstreg.append("BF");
    lstreg.append("71");

    lstreg.append("Seno");
    lstreg.append("BF");
    lstreg.append("72");

    lstreg.append("Sissili");
    lstreg.append("BF");
    lstreg.append("73");

    lstreg.append("Sourou");
    lstreg.append("BF");
    lstreg.append("74");

    lstreg.append("Tuy");
    lstreg.append("BF");
    lstreg.append("75");

    lstreg.append("Yagha");
    lstreg.append("BF");
    lstreg.append("76");

    lstreg.append("Yatenga");
    lstreg.append("BF");
    lstreg.append("77");

    lstreg.append("Ziro");
    lstreg.append("BF");
    lstreg.append("78");

    lstreg.append("Zondoma");
    lstreg.append("BG");
    lstreg.append("33");

    lstreg.append("Mikhaylovgrad");
    lstreg.append("BG");
    lstreg.append("38");

    lstreg.append("Blagoevgrad");
    lstreg.append("BG");
    lstreg.append("39");

    lstreg.append("Burgas");
    lstreg.append("BG");
    lstreg.append("40");

    lstreg.append("Dobrich");
    lstreg.append("BG");
    lstreg.append("41");

    lstreg.append("Gabrovo");
    lstreg.append("BG");
    lstreg.append("42");

    lstreg.append("Grad Sofiya");
    lstreg.append("BG");
    lstreg.append("43");

    lstreg.append("Khaskovo");
    lstreg.append("BG");
    lstreg.append("44");

    lstreg.append("Kurdzhali");
    lstreg.append("BG");
    lstreg.append("45");

    lstreg.append("Kyustendil");
    lstreg.append("BG");
    lstreg.append("46");

    lstreg.append("Lovech");
    lstreg.append("BG");
    lstreg.append("47");

    lstreg.append("Montana");
    lstreg.append("BG");
    lstreg.append("48");

    lstreg.append("Pazardzhik");
    lstreg.append("BG");
    lstreg.append("49");

    lstreg.append("Pernik");
    lstreg.append("BG");
    lstreg.append("50");

    lstreg.append("Pleven");
    lstreg.append("BG");
    lstreg.append("51");

    lstreg.append("Plovdiv");
    lstreg.append("BG");
    lstreg.append("52");

    lstreg.append("Razgrad");
    lstreg.append("BG");
    lstreg.append("53");

    lstreg.append("Ruse");
    lstreg.append("BG");
    lstreg.append("54");

    lstreg.append("Shumen");
    lstreg.append("BG");
    lstreg.append("55");

    lstreg.append("Silistra");
    lstreg.append("BG");
    lstreg.append("56");

    lstreg.append("Sliven");
    lstreg.append("BG");
    lstreg.append("57");

    lstreg.append("Smolyan");
    lstreg.append("BG");
    lstreg.append("58");

    lstreg.append("Sofiya");
    lstreg.append("BG");
    lstreg.append("59");

    lstreg.append("Stara Zagora");
    lstreg.append("BG");
    lstreg.append("60");

    lstreg.append("Turgovishte");
    lstreg.append("BG");
    lstreg.append("61");

    lstreg.append("Varna");
    lstreg.append("BG");
    lstreg.append("62");

    lstreg.append("Veliko Turnovo");
    lstreg.append("BG");
    lstreg.append("63");

    lstreg.append("Vidin");
    lstreg.append("BG");
    lstreg.append("64");

    lstreg.append("Vratsa");
    lstreg.append("BG");
    lstreg.append("65");

    lstreg.append("Yambol");
    lstreg.append("BH");
    lstreg.append("01");

    lstreg.append("Al Hadd");
    lstreg.append("BH");
    lstreg.append("02");

    lstreg.append("Al Manamah");
    lstreg.append("BH");
    lstreg.append("05");

    lstreg.append("Jidd Hafs");
    lstreg.append("BH");
    lstreg.append("06");

    lstreg.append("Sitrah");
    lstreg.append("BH");
    lstreg.append("08");

    lstreg.append("Al Mintaqah al Gharbiyah");
    lstreg.append("BH");
    lstreg.append("09");

    lstreg.append("Mintaqat Juzur Hawar");
    lstreg.append("BH");
    lstreg.append("10");

    lstreg.append("Al Mintaqah ash Shamaliyah");
    lstreg.append("BH");
    lstreg.append("11");

    lstreg.append("Al Mintaqah al Wusta");
    lstreg.append("BH");
    lstreg.append("12");

    lstreg.append("Madinat");
    lstreg.append("BH");
    lstreg.append("13");

    lstreg.append("Ar Rifa");
    lstreg.append("BH");
    lstreg.append("14");

    lstreg.append("Madinat Hamad");
    lstreg.append("BH");
    lstreg.append("15");

    lstreg.append("Al Muharraq");
    lstreg.append("BH");
    lstreg.append("16");

    lstreg.append("Al Asimah");
    lstreg.append("BH");
    lstreg.append("17");

    lstreg.append("Al Janubiyah");
    lstreg.append("BH");
    lstreg.append("18");

    lstreg.append("Ash Shamaliyah");
    lstreg.append("BH");
    lstreg.append("19");

    lstreg.append("Al Wusta");
    lstreg.append("BI");
    lstreg.append("02");

    lstreg.append("Bujumbura");
    lstreg.append("BI");
    lstreg.append("09");

    lstreg.append("Bubanza");
    lstreg.append("BI");
    lstreg.append("10");

    lstreg.append("Bururi");
    lstreg.append("BI");
    lstreg.append("11");

    lstreg.append("Cankuzo");
    lstreg.append("BI");
    lstreg.append("12");

    lstreg.append("Cibitoke");
    lstreg.append("BI");
    lstreg.append("13");

    lstreg.append("Gitega");
    lstreg.append("BI");
    lstreg.append("14");

    lstreg.append("Karuzi");
    lstreg.append("BI");
    lstreg.append("15");

    lstreg.append("Kayanza");
    lstreg.append("BI");
    lstreg.append("16");

    lstreg.append("Kirundo");
    lstreg.append("BI");
    lstreg.append("17");

    lstreg.append("Makamba");
    lstreg.append("BI");
    lstreg.append("18");

    lstreg.append("Muyinga");
    lstreg.append("BI");
    lstreg.append("19");

    lstreg.append("Ngozi");
    lstreg.append("BI");
    lstreg.append("20");

    lstreg.append("Rutana");
    lstreg.append("BI");
    lstreg.append("21");

    lstreg.append("Ruyigi");
    lstreg.append("BI");
    lstreg.append("22");

    lstreg.append("Muramvya");
    lstreg.append("BI");
    lstreg.append("23");

    lstreg.append("Mwaro");
    lstreg.append("BJ");
    lstreg.append("07");

    lstreg.append("Alibori");
    lstreg.append("BJ");
    lstreg.append("08");

    lstreg.append("Atakora");
    lstreg.append("BJ");
    lstreg.append("09");

    lstreg.append("Atlanyique");
    lstreg.append("BJ");
    lstreg.append("10");

    lstreg.append("Borgou");
    lstreg.append("BJ");
    lstreg.append("11");

    lstreg.append("Collines");
    lstreg.append("BJ");
    lstreg.append("12");

    lstreg.append("Kouffo");
    lstreg.append("BJ");
    lstreg.append("13");

    lstreg.append("Donga");
    lstreg.append("BJ");
    lstreg.append("14");

    lstreg.append("Littoral");
    lstreg.append("BJ");
    lstreg.append("15");

    lstreg.append("Mono");
    lstreg.append("BJ");
    lstreg.append("16");

    lstreg.append("Oueme");
    lstreg.append("BJ");
    lstreg.append("17");

    lstreg.append("Plateau");
    lstreg.append("BJ");
    lstreg.append("18");

    lstreg.append("Zou");
    lstreg.append("BM");
    lstreg.append("01");

    lstreg.append("Devonshire");
    lstreg.append("BM");
    lstreg.append("02");

    lstreg.append("Hamilton");
    lstreg.append("BM");
    lstreg.append("03");

    lstreg.append("Hamilton");
    lstreg.append("BM");
    lstreg.append("04");

    lstreg.append("Paget");
    lstreg.append("BM");
    lstreg.append("05");

    lstreg.append("Pembroke");
    lstreg.append("BM");
    lstreg.append("06");

    lstreg.append("Saint George");
    lstreg.append("BM");
    lstreg.append("07");

    lstreg.append("Saint George's");
    lstreg.append("BM");
    lstreg.append("08");

    lstreg.append("Sandys");
    lstreg.append("BM");
    lstreg.append("09");

    lstreg.append("Smiths");
    lstreg.append("BM");
    lstreg.append("10");

    lstreg.append("Southampton");
    lstreg.append("BM");
    lstreg.append("11");

    lstreg.append("Warwick");
    lstreg.append("BN");
    lstreg.append("07");

    lstreg.append("Alibori");
    lstreg.append("BN");
    lstreg.append("08");

    lstreg.append("Belait");
    lstreg.append("BN");
    lstreg.append("09");

    lstreg.append("Brunei and Muara");
    lstreg.append("BN");
    lstreg.append("10");

    lstreg.append("Temburong");
    lstreg.append("BN");
    lstreg.append("11");

    lstreg.append("Collines");
    lstreg.append("BN");
    lstreg.append("12");

    lstreg.append("Kouffo");
    lstreg.append("BN");
    lstreg.append("13");

    lstreg.append("Donga");
    lstreg.append("BN");
    lstreg.append("14");

    lstreg.append("Littoral");
    lstreg.append("BN");
    lstreg.append("15");

    lstreg.append("Tutong");
    lstreg.append("BN");
    lstreg.append("16");

    lstreg.append("Oueme");
    lstreg.append("BN");
    lstreg.append("17");

    lstreg.append("Plateau");
    lstreg.append("BN");
    lstreg.append("18");

    lstreg.append("Zou");
    lstreg.append("BO");
    lstreg.append("01");

    lstreg.append("Chuquisaca");
    lstreg.append("BO");
    lstreg.append("02");

    lstreg.append("Cochabamba");
    lstreg.append("BO");
    lstreg.append("03");

    lstreg.append("El Beni");
    lstreg.append("BO");
    lstreg.append("04");

    lstreg.append("La Paz");
    lstreg.append("BO");
    lstreg.append("05");

    lstreg.append("Oruro");
    lstreg.append("BO");
    lstreg.append("06");

    lstreg.append("Pando");
    lstreg.append("BO");
    lstreg.append("07");

    lstreg.append("Potosi");
    lstreg.append("BO");
    lstreg.append("08");

    lstreg.append("Santa Cruz");
    lstreg.append("BO");
    lstreg.append("09");

    lstreg.append("Tarija");
    lstreg.append("BR");
    lstreg.append("01");

    lstreg.append("Acre");
    lstreg.append("BR");
    lstreg.append("02");

    lstreg.append("Alagoas");
    lstreg.append("BR");
    lstreg.append("03");

    lstreg.append("Amapa");
    lstreg.append("BR");
    lstreg.append("04");

    lstreg.append("Amazonas");
    lstreg.append("BR");
    lstreg.append("05");

    lstreg.append("Bahia");
    lstreg.append("BR");
    lstreg.append("06");

    lstreg.append("Ceara");
    lstreg.append("BR");
    lstreg.append("07");

    lstreg.append("Distrito Federal");
    lstreg.append("BR");
    lstreg.append("08");

    lstreg.append("Espirito Santo");
    lstreg.append("BR");
    lstreg.append("11");

    lstreg.append("Mato Grosso do Sul");
    lstreg.append("BR");
    lstreg.append("13");

    lstreg.append("Maranhao");
    lstreg.append("BR");
    lstreg.append("14");

    lstreg.append("Mato Grosso");
    lstreg.append("BR");
    lstreg.append("15");

    lstreg.append("Minas Gerais");
    lstreg.append("BR");
    lstreg.append("16");

    lstreg.append("Para");
    lstreg.append("BR");
    lstreg.append("17");

    lstreg.append("Paraiba");
    lstreg.append("BR");
    lstreg.append("18");

    lstreg.append("Parana");
    lstreg.append("BR");
    lstreg.append("20");

    lstreg.append("Piaui");
    lstreg.append("BR");
    lstreg.append("21");

    lstreg.append("Rio de Janeiro");
    lstreg.append("BR");
    lstreg.append("22");

    lstreg.append("Rio Grande do Norte");
    lstreg.append("BR");
    lstreg.append("23");

    lstreg.append("Rio Grande do Sul");
    lstreg.append("BR");
    lstreg.append("24");

    lstreg.append("Rondonia");
    lstreg.append("BR");
    lstreg.append("25");

    lstreg.append("Roraima");
    lstreg.append("BR");
    lstreg.append("26");

    lstreg.append("Santa Catarina");
    lstreg.append("BR");
    lstreg.append("27");

    lstreg.append("Sao Paulo");
    lstreg.append("BR");
    lstreg.append("28");

    lstreg.append("Sergipe");
    lstreg.append("BR");
    lstreg.append("29");

    lstreg.append("Goias");
    lstreg.append("BR");
    lstreg.append("30");

    lstreg.append("Pernambuco");
    lstreg.append("BR");
    lstreg.append("31");

    lstreg.append("Tocantins");
    lstreg.append("BS");
    lstreg.append("05");

    lstreg.append("Bimini");
    lstreg.append("BS");
    lstreg.append("06");

    lstreg.append("Cat Island");
    lstreg.append("BS");
    lstreg.append("10");

    lstreg.append("Exuma");
    lstreg.append("BS");
    lstreg.append("13");

    lstreg.append("Inagua");
    lstreg.append("BS");
    lstreg.append("15");

    lstreg.append("Long Island");
    lstreg.append("BS");
    lstreg.append("16");

    lstreg.append("Mayaguana");
    lstreg.append("BS");
    lstreg.append("18");

    lstreg.append("Ragged Island");
    lstreg.append("BS");
    lstreg.append("22");

    lstreg.append("Harbour Island");
    lstreg.append("BS");
    lstreg.append("23");

    lstreg.append("New Providence");
    lstreg.append("BS");
    lstreg.append("24");

    lstreg.append("Acklins and Crooked Islands");
    lstreg.append("BS");
    lstreg.append("25");

    lstreg.append("Freeport");
    lstreg.append("BS");
    lstreg.append("26");

    lstreg.append("Fresh Creek");
    lstreg.append("BS");
    lstreg.append("27");

    lstreg.append("Governor's Harbour");
    lstreg.append("BS");
    lstreg.append("28");

    lstreg.append("Green Turtle Cay");
    lstreg.append("BS");
    lstreg.append("29");

    lstreg.append("High Rock");
    lstreg.append("BS");
    lstreg.append("30");

    lstreg.append("Kemps Bay");
    lstreg.append("BS");
    lstreg.append("31");

    lstreg.append("Marsh Harbour");
    lstreg.append("BS");
    lstreg.append("32");

    lstreg.append("Nichollstown and Berry Islands");
    lstreg.append("BS");
    lstreg.append("33");

    lstreg.append("Rock Sound");
    lstreg.append("BS");
    lstreg.append("34");

    lstreg.append("Sandy Point");
    lstreg.append("BS");
    lstreg.append("35");

    lstreg.append("San Salvador and Rum Cay");
    lstreg.append("BT");
    lstreg.append("05");

    lstreg.append("Bumthang");
    lstreg.append("BT");
    lstreg.append("06");

    lstreg.append("Chhukha");
    lstreg.append("BT");
    lstreg.append("07");

    lstreg.append("Chirang");
    lstreg.append("BT");
    lstreg.append("08");

    lstreg.append("Daga");
    lstreg.append("BT");
    lstreg.append("09");

    lstreg.append("Geylegphug");
    lstreg.append("BT");
    lstreg.append("10");

    lstreg.append("Ha");
    lstreg.append("BT");
    lstreg.append("11");

    lstreg.append("Lhuntshi");
    lstreg.append("BT");
    lstreg.append("12");

    lstreg.append("Mongar");
    lstreg.append("BT");
    lstreg.append("13");

    lstreg.append("Paro");
    lstreg.append("BT");
    lstreg.append("14");

    lstreg.append("Pemagatsel");
    lstreg.append("BT");
    lstreg.append("15");

    lstreg.append("Punakha");
    lstreg.append("BT");
    lstreg.append("16");

    lstreg.append("Samchi");
    lstreg.append("BT");
    lstreg.append("17");

    lstreg.append("Samdrup");
    lstreg.append("BT");
    lstreg.append("18");

    lstreg.append("Shemgang");
    lstreg.append("BT");
    lstreg.append("19");

    lstreg.append("Tashigang");
    lstreg.append("BT");
    lstreg.append("20");

    lstreg.append("Thimphu");
    lstreg.append("BT");
    lstreg.append("21");

    lstreg.append("Tongsa");
    lstreg.append("BT");
    lstreg.append("22");

    lstreg.append("Wangdi Phodrang");
    lstreg.append("BW");
    lstreg.append("01");

    lstreg.append("Central");
    lstreg.append("BW");
    lstreg.append("03");

    lstreg.append("Ghanzi");
    lstreg.append("BW");
    lstreg.append("04");

    lstreg.append("Kgalagadi");
    lstreg.append("BW");
    lstreg.append("05");

    lstreg.append("Kgatleng");
    lstreg.append("BW");
    lstreg.append("06");

    lstreg.append("Kweneng");
    lstreg.append("BW");
    lstreg.append("08");

    lstreg.append("North-East");
    lstreg.append("BW");
    lstreg.append("09");

    lstreg.append("South-East");
    lstreg.append("BW");
    lstreg.append("10");

    lstreg.append("Southern");
    lstreg.append("BW");
    lstreg.append("11");

    lstreg.append("North-West");
    lstreg.append("BY");
    lstreg.append("01");

    lstreg.append("Brestskaya Voblasts'");
    lstreg.append("BY");
    lstreg.append("02");

    lstreg.append("Homyel'skaya Voblasts'");
    lstreg.append("BY");
    lstreg.append("03");

    lstreg.append("Hrodzyenskaya Voblasts'");
    lstreg.append("BY");
    lstreg.append("04");

    lstreg.append("Minsk");
    lstreg.append("BY");
    lstreg.append("05");

    lstreg.append("Minskaya Voblasts'");
    lstreg.append("BY");
    lstreg.append("06");

    lstreg.append("Mahilyowskaya Voblasts'");
    lstreg.append("BY");
    lstreg.append("07");

    lstreg.append("Vitsyebskaya Voblasts'");
    lstreg.append("BZ");
    lstreg.append("01");

    lstreg.append("Belize");
    lstreg.append("BZ");
    lstreg.append("02");

    lstreg.append("Cayo");
    lstreg.append("BZ");
    lstreg.append("03");

    lstreg.append("Corozal");
    lstreg.append("BZ");
    lstreg.append("04");

    lstreg.append("Orange Walk");
    lstreg.append("BZ");
    lstreg.append("05");

    lstreg.append("Stann Creek");
    lstreg.append("BZ");
    lstreg.append("06");

    lstreg.append("Toledo");
    lstreg.append("CA");
    lstreg.append("01");

    lstreg.append("Alberta");
    lstreg.append("CA");
    lstreg.append("02");

    lstreg.append("British Columbia");
    lstreg.append("CA");
    lstreg.append("03");

    lstreg.append("Manitoba");
    lstreg.append("CA");
    lstreg.append("04");

    lstreg.append("New Brunswick");
    lstreg.append("CA");
    lstreg.append("05");

    lstreg.append("Newfoundland and Labrador");
    lstreg.append("CA");
    lstreg.append("07");

    lstreg.append("Nova Scotia");
    lstreg.append("CA");
    lstreg.append("08");

    lstreg.append("Ontario");
    lstreg.append("CA");
    lstreg.append("09");

    lstreg.append("Prince Edward Island");
    lstreg.append("CA");
    lstreg.append("10");

    lstreg.append("Quebec");
    lstreg.append("CA");
    lstreg.append("11");

    lstreg.append("Saskatchewan");
    lstreg.append("CA");
    lstreg.append("12");

    lstreg.append("Yukon Territory");
    lstreg.append("CA");
    lstreg.append("13");

    lstreg.append("Northwest Territories");
    lstreg.append("CA");
    lstreg.append("14");

    lstreg.append("Nunavut");
    lstreg.append("CD");
    lstreg.append("01");

    lstreg.append("Bandundu");
    lstreg.append("CD");
    lstreg.append("02");

    lstreg.append("Equateur");
    lstreg.append("CD");
    lstreg.append("04");

    lstreg.append("Kasai-Oriental");
    lstreg.append("CD");
    lstreg.append("05");

    lstreg.append("Katanga");
    lstreg.append("CD");
    lstreg.append("06");

    lstreg.append("Kinshasa");
    lstreg.append("CD");
    lstreg.append("08");

    lstreg.append("Bas-Congo");
    lstreg.append("CD");
    lstreg.append("09");

    lstreg.append("Orientale");
    lstreg.append("CD");
    lstreg.append("10");

    lstreg.append("Maniema");
    lstreg.append("CD");
    lstreg.append("11");

    lstreg.append("Nord-Kivu");
    lstreg.append("CD");
    lstreg.append("12");

    lstreg.append("Sud-Kivu");
    lstreg.append("CF");
    lstreg.append("01");

    lstreg.append("Bamingui-Bangoran");
    lstreg.append("CF");
    lstreg.append("02");

    lstreg.append("Basse-Kotto");
    lstreg.append("CF");
    lstreg.append("03");

    lstreg.append("Haute-Kotto");
    lstreg.append("CF");
    lstreg.append("04");

    lstreg.append("Mambere-Kadei");
    lstreg.append("CF");
    lstreg.append("05");

    lstreg.append("Haut-Mbomou");
    lstreg.append("CF");
    lstreg.append("06");

    lstreg.append("Kemo");
    lstreg.append("CF");
    lstreg.append("07");

    lstreg.append("Lobaye");
    lstreg.append("CF");
    lstreg.append("08");

    lstreg.append("Mbomou");
    lstreg.append("CF");
    lstreg.append("09");

    lstreg.append("Nana-Mambere");
    lstreg.append("CF");
    lstreg.append("11");

    lstreg.append("Ouaka");
    lstreg.append("CF");
    lstreg.append("12");

    lstreg.append("Ouham");
    lstreg.append("CF");
    lstreg.append("13");

    lstreg.append("Ouham-Pende");
    lstreg.append("CF");
    lstreg.append("14");

    lstreg.append("Cuvette-Ouest");
    lstreg.append("CF");
    lstreg.append("15");

    lstreg.append("Nana-Grebizi");
    lstreg.append("CF");
    lstreg.append("16");

    lstreg.append("Sangha-Mbaere");
    lstreg.append("CF");
    lstreg.append("17");

    lstreg.append("Ombella-Mpoko");
    lstreg.append("CF");
    lstreg.append("18");

    lstreg.append("Bangui");
    lstreg.append("CG");
    lstreg.append("01");

    lstreg.append("Bouenza");
    lstreg.append("CG");
    lstreg.append("04");

    lstreg.append("Kouilou");
    lstreg.append("CG");
    lstreg.append("05");

    lstreg.append("Lekoumou");
    lstreg.append("CG");
    lstreg.append("06");

    lstreg.append("Likouala");
    lstreg.append("CG");
    lstreg.append("07");

    lstreg.append("Niari");
    lstreg.append("CG");
    lstreg.append("08");

    lstreg.append("Plateaux");
    lstreg.append("CG");
    lstreg.append("10");

    lstreg.append("Sangha");
    lstreg.append("CG");
    lstreg.append("11");

    lstreg.append("Pool");
    lstreg.append("CG");
    lstreg.append("12");

    lstreg.append("Brazzaville");
    lstreg.append("CG");
    lstreg.append("13");

    lstreg.append("Cuvette");
    lstreg.append("CG");
    lstreg.append("14");

    lstreg.append("Cuvette-Ouest");
    lstreg.append("CH");
    lstreg.append("01");

    lstreg.append("Aargau");
    lstreg.append("CH");
    lstreg.append("02");

    lstreg.append("Ausser-Rhoden");
    lstreg.append("CH");
    lstreg.append("03");

    lstreg.append("Basel-Landschaft");
    lstreg.append("CH");
    lstreg.append("04");

    lstreg.append("Basel-Stadt");
    lstreg.append("CH");
    lstreg.append("05");

    lstreg.append("Bern");
    lstreg.append("CH");
    lstreg.append("06");

    lstreg.append("Fribourg");
    lstreg.append("CH");
    lstreg.append("07");

    lstreg.append("Geneve");
    lstreg.append("CH");
    lstreg.append("08");

    lstreg.append("Glarus");
    lstreg.append("CH");
    lstreg.append("09");

    lstreg.append("Graubunden");
    lstreg.append("CH");
    lstreg.append("10");

    lstreg.append("Inner-Rhoden");
    lstreg.append("CH");
    lstreg.append("11");

    lstreg.append("Luzern");
    lstreg.append("CH");
    lstreg.append("12");

    lstreg.append("Neuchatel");
    lstreg.append("CH");
    lstreg.append("13");

    lstreg.append("Nidwalden");
    lstreg.append("CH");
    lstreg.append("14");

    lstreg.append("Obwalden");
    lstreg.append("CH");
    lstreg.append("15");

    lstreg.append("Sankt Gallen");
    lstreg.append("CH");
    lstreg.append("16");

    lstreg.append("Schaffhausen");
    lstreg.append("CH");
    lstreg.append("17");

    lstreg.append("Schwyz");
    lstreg.append("CH");
    lstreg.append("18");

    lstreg.append("Solothurn");
    lstreg.append("CH");
    lstreg.append("19");

    lstreg.append("Thurgau");
    lstreg.append("CH");
    lstreg.append("20");

    lstreg.append("Ticino");
    lstreg.append("CH");
    lstreg.append("21");

    lstreg.append("Uri");
    lstreg.append("CH");
    lstreg.append("22");

    lstreg.append("Valais");
    lstreg.append("CH");
    lstreg.append("23");

    lstreg.append("Vaud");
    lstreg.append("CH");
    lstreg.append("24");

    lstreg.append("Zug");
    lstreg.append("CH");
    lstreg.append("25");

    lstreg.append("Zurich");
    lstreg.append("CH");
    lstreg.append("26");

    lstreg.append("Jura");
    lstreg.append("CI");
    lstreg.append("74");

    lstreg.append("Agneby");
    lstreg.append("CI");
    lstreg.append("75");

    lstreg.append("Bafing");
    lstreg.append("CI");
    lstreg.append("76");

    lstreg.append("Bas-Sassandra");
    lstreg.append("CI");
    lstreg.append("77");

    lstreg.append("Denguele");
    lstreg.append("CI");
    lstreg.append("78");

    lstreg.append("Dix-Huit Montagnes");
    lstreg.append("CI");
    lstreg.append("79");

    lstreg.append("Fromager");
    lstreg.append("CI");
    lstreg.append("80");

    lstreg.append("Haut-Sassandra");
    lstreg.append("CI");
    lstreg.append("81");

    lstreg.append("Lacs");
    lstreg.append("CI");
    lstreg.append("82");

    lstreg.append("Lagunes");
    lstreg.append("CI");
    lstreg.append("83");

    lstreg.append("Marahoue");
    lstreg.append("CI");
    lstreg.append("84");

    lstreg.append("Moyen-Cavally");
    lstreg.append("CI");
    lstreg.append("85");


    lst.append("A1");
    lst.append("Anonymous Proxy");
    lst.append("A2");
    lst.append("Satellite Provider");
    lst.append("AD");
    lst.append("Andorra");
    lst.append("AE");
    lst.append("United Arab Emirates");
    lst.append("AF");
    lst.append("Afghanistan");
    lst.append("AG");
    lst.append("Antigua and Barbuda");
    lst.append("AI");
    lst.append("Anguilla");
    lst.append("AL");
    lst.append("Albania");
    lst.append("AM");
    lst.append("Armenia");
    lst.append("AN");
    lst.append("Netherlands Antilles");
    lst.append("AO");
    lst.append("Angola");
    lst.append("AP");
    lst.append("Asia/Pacific Region");
    lst.append("AQ");
    lst.append("Antarctica");
    lst.append("AR");
    lst.append("Argentina");
    lst.append("AS");
    lst.append("American Samoa");
    lst.append("AT");
    lst.append("Austria");
    lst.append("AU");
    lst.append("Australia");
    lst.append("AW");
    lst.append("Aruba");
    lst.append("AX");
    lst.append("Aland Islands");
    lst.append("AZ");
    lst.append("Azerbaijan");
    lst.append("BA");
    lst.append("Bosnia and Herzegovina");
    lst.append("BB");
    lst.append("Barbados");
    lst.append("BD");
    lst.append("Bangladesh");
    lst.append("BE");
    lst.append("Belgium");
    lst.append("BF");
    lst.append("Burkina Faso");
    lst.append("BG");
    lst.append("Bulgaria");
    lst.append("BH");
    lst.append("Bahrain");
    lst.append("BI");
    lst.append("Burundi");
    lst.append("BJ");
    lst.append("Benin");
    lst.append("BM");
    lst.append("Bermuda");
    lst.append("BN");
    lst.append("Brunei Darussalam");
    lst.append("BO");
    lst.append("Bolivia");
    lst.append("BR");
    lst.append("Brazil");
    lst.append("BS");
    lst.append("Bahamas");
    lst.append("BT");
    lst.append("Bhutan");
    lst.append("BV");
    lst.append("Bouvet Island");
    lst.append("BW");
    lst.append("Botswana");
    lst.append("BY");
    lst.append("Belarus");
    lst.append("BZ");
    lst.append("Belize");
    lst.append("CA");
    lst.append("Canada");
    lst.append("CC");
    lst.append("Cocos (Keeling) Islands");
    lst.append("CD");
    lst.append("Congo");
    lst.append("CF");
    lst.append("Central African Republic");
    lst.append("CG");
    lst.append("Congo");
    lst.append("CH");
    lst.append("Switzerland");
    lst.append("CI");
    lst.append("Cote d'Ivoire");
    lst.append("CK");
    lst.append("Cook Islands");
    lst.append("CL");
    lst.append("Chile");
    lst.append("CM");
    lst.append("Cameroon");
    lst.append("CN");
    lst.append("China");
    lst.append("CO");
    lst.append("Colombia");
    lst.append("CR");
    lst.append("Costa Rica");
    lst.append("CU");
    lst.append("Cuba");
    lst.append("CV");
    lst.append("Cape Verde");
    lst.append("CX");
    lst.append("Christmas Island");
    lst.append("CY");
    lst.append("Cyprus");
    lst.append("CZ");
    lst.append("Czech Republic");
    lst.append("DE");
    lst.append("Germany");
    lst.append("DJ");
    lst.append("Djibouti");
    lst.append("DK");
    lst.append("Denmark");
    lst.append("DM");
    lst.append("Dominica");
    lst.append("DO");
    lst.append("Dominican Republic");
    lst.append("DZ");
    lst.append("Algeria");
    lst.append("EC");
    lst.append("Ecuador");
    lst.append("EE");
    lst.append("Estonia");
    lst.append("EG");
    lst.append("Egypt");
    lst.append("EH");
    lst.append("Western Sahara");
    lst.append("ER");
    lst.append("Eritrea");
    lst.append("ES");
    lst.append("Spain");
    lst.append("ET");
    lst.append("Ethiopia");
    lst.append("EU");
    lst.append("Europe");
    lst.append("FI");
    lst.append("Finland");
    lst.append("FJ");
    lst.append("Fiji");
    lst.append("FK");
    lst.append("Falkland Islands (Malvinas)");
    lst.append("FM");
    lst.append("Micronesia");
    lst.append("FO");
    lst.append("Faroe Islands");
    lst.append("FR");
    lst.append("France");
    lst.append("GA");
    lst.append("Gabon");
    lst.append("GB");
    lst.append("United Kingdom");
    lst.append("GD");
    lst.append("Grenada");
    lst.append("GE");
    lst.append("Georgia");
    lst.append("GF");
    lst.append("French Guiana");
    lst.append("GG");
    lst.append("Guernsey");
    lst.append("GH");
    lst.append("Ghana");
    lst.append("GI");
    lst.append("Gibraltar");
    lst.append("GL");
    lst.append("Greenland");
    lst.append("GM");
    lst.append("Gambia");
    lst.append("GN");
    lst.append("Guinea");
    lst.append("GP");
    lst.append("Guadeloupe");
    lst.append("GQ");
    lst.append("Equatorial Guinea");
    lst.append("GR");
    lst.append("Greece");
    lst.append("GS");
    lst.append("South Georgia and the South Sandwich Islands");
    lst.append("GT");
    lst.append("Guatemala");
    lst.append("GU");
    lst.append("Guam");
    lst.append("GW");
    lst.append("Guinea-Bissau");
    lst.append("GY");
    lst.append("Guyana");
    lst.append("HK");
    lst.append("Hong Kong");
    lst.append("HM");
    lst.append("Heard Island and McDonald Islands");
    lst.append("HN");
    lst.append("Honduras");
    lst.append("HR");
    lst.append("Croatia");
    lst.append("HT");
    lst.append("Haiti");
    lst.append("HU");
    lst.append("Hungary");
    lst.append("ID");
    lst.append("Indonesia");
    lst.append("IE");
    lst.append("Ireland");
    lst.append("IL");
    lst.append("Israel");
    lst.append("IM");
    lst.append("Isle of Man");
    lst.append("IN");
    lst.append("India");
    lst.append("IO");
    lst.append("British Indian Ocean Territory");
    lst.append("IQ");
    lst.append("Iraq");
    lst.append("IR");
    lst.append("Iran");
    lst.append("IS");
    lst.append("Iceland");
    lst.append("IT");
    lst.append("Italy");
    lst.append("JE");
    lst.append("Jersey");
    lst.append("JM");
    lst.append("Jamaica");
    lst.append("JO");
    lst.append("Jordan");
    lst.append("JP");
    lst.append("Japan");
    lst.append("KE");
    lst.append("Kenya");
    lst.append("KG");
    lst.append("Kyrgyzstan");
    lst.append("KH");
    lst.append("Cambodia");
    lst.append("KI");
    lst.append("Kiribati");
    lst.append("KM");
    lst.append("Comoros");
    lst.append("KN");
    lst.append("Saint Kitts and Nevis");
    lst.append("KP");
    lst.append("Korea (KP)");
    lst.append("KR");
    lst.append("Korea (KR)");
    lst.append("KW");
    lst.append("Kuwait");
    lst.append("KY");
    lst.append("Cayman Islands");
    lst.append("KZ");
    lst.append("Kazakhstan");
    lst.append("LA");
    lst.append("Lao People's Democratic Republic");
    lst.append("LB");
    lst.append("Lebanon");
    lst.append("LC");
    lst.append("Saint Lucia");
    lst.append("LI");
    lst.append("Liechtenstein");
    lst.append("LK");
    lst.append("Sri Lanka");
    lst.append("LR");
    lst.append("Liberia");
    lst.append("LS");
    lst.append("Lesotho");
    lst.append("LT");
    lst.append("Lithuania");
    lst.append("LU");
    lst.append("Luxembourg");
    lst.append("LV");
    lst.append("Latvia");
    lst.append("LY");
    lst.append("Libyan Arab Jamahiriya");
    lst.append("MA");
    lst.append("Morocco");
    lst.append("MC");
    lst.append("Monaco");
    lst.append("MD");
    lst.append("Moldova");
    lst.append("ME");
    lst.append("Montenegro");
    lst.append("MG");
    lst.append("Madagascar");
    lst.append("MH");
    lst.append("Marshall Islands");
    lst.append("MK");
    lst.append("Macedonia");
    lst.append("ML");
    lst.append("Mali");
    lst.append("MM");
    lst.append("Myanmar");
    lst.append("MN");
    lst.append("Mongolia");
    lst.append("MO");
    lst.append("Macao");
    lst.append("MP");
    lst.append("Northern Mariana Islands");
    lst.append("MQ");
    lst.append("Martinique");
    lst.append("MR");
    lst.append("Mauritania");
    lst.append("MS");
    lst.append("Montserrat");
    lst.append("MT");
    lst.append("Malta");
    lst.append("MU");
    lst.append("Mauritius");
    lst.append("MV");
    lst.append("Maldives");
    lst.append("MW");
    lst.append("Malawi");
    lst.append("MX");
    lst.append("Mexico");
    lst.append("MY");
    lst.append("Malaysia");
    lst.append("MZ");
    lst.append("Mozambique");
    lst.append("NA");
    lst.append("Namibia");
    lst.append("NC");
    lst.append("New Caledonia");
    lst.append("NE");
    lst.append("Niger");
    lst.append("NF");
    lst.append("Norfolk Island");
    lst.append("NG");
    lst.append("Nigeria");
    lst.append("NI");
    lst.append("Nicaragua");
    lst.append("NL");
    lst.append("Netherlands");
    lst.append("NO");
    lst.append("Norway");
    lst.append("NP");
    lst.append("Nepal");
    lst.append("NR");
    lst.append("Nauru");
    lst.append("NU");
    lst.append("Niue");
    lst.append("NZ");
    lst.append("New Zealand");
    lst.append("OM");
    lst.append("Oman");
    lst.append("PA");
    lst.append("Panama");
    lst.append("PE");
    lst.append("Peru");
    lst.append("PF");
    lst.append("French Polynesia");
    lst.append("PG");
    lst.append("Papua New Guinea");
    lst.append("PH");
    lst.append("Philippines");
    lst.append("PK");
    lst.append("Pakistan");
    lst.append("PL");
    lst.append("Poland");
    lst.append("PM");
    lst.append("Saint Pierre and Miquelon");
    lst.append("PN");
    lst.append("Pitcairn");
    lst.append("PR");
    lst.append("Puerto Rico");
    lst.append("PS");
    lst.append("Palestinian Territory");
    lst.append("PT");
    lst.append("Portugal");
    lst.append("PW");
    lst.append("Palau");
    lst.append("PY");
    lst.append("Paraguay");
    lst.append("QA");
    lst.append("Qatar");
    lst.append("RE");
    lst.append("Reunion");
    lst.append("RO");
    lst.append("Romania");
    lst.append("RS");
    lst.append("Serbia");
    lst.append("RU");
    lst.append("Russian Federation");
    lst.append("RW");
    lst.append("Rwanda");
    lst.append("SA");
    lst.append("Saudi Arabia");
    lst.append("SB");
    lst.append("Solomon Islands");
    lst.append("SC");
    lst.append("Seychelles");
    lst.append("SD");
    lst.append("Sudan");
    lst.append("SE");
    lst.append("Sweden");
    lst.append("SG");
    lst.append("Singapore");
    lst.append("SH");
    lst.append("Saint Helena");
    lst.append("SI");
    lst.append("Slovenia");
    lst.append("SJ");
    lst.append("Svalbard and Jan Mayen");
    lst.append("SK");
    lst.append("Slovakia");
    lst.append("SL");
    lst.append("Sierra Leone");
    lst.append("SM");
    lst.append("San Marino");
    lst.append("SN");
    lst.append("Senegal");
    lst.append("SO");
    lst.append("Somalia");
    lst.append("SR");
    lst.append("Suriname");
    lst.append("ST");
    lst.append("Sao Tome and Principe");
    lst.append("SV");
    lst.append("El Salvador");
    lst.append("SY");
    lst.append("Syrian Arab Republic");
    lst.append("SZ");
    lst.append("Swaziland");
    lst.append("TC");
    lst.append("Turks and Caicos Islands");
    lst.append("TD");
    lst.append("Chad");
    lst.append("TF");
    lst.append("French Southern Territories");
    lst.append("TG");
    lst.append("Togo");
    lst.append("TH");
    lst.append("Thailand");
    lst.append("TJ");
    lst.append("Tajikistan");
    lst.append("TK");
    lst.append("Tokelau");
    lst.append("TL");
    lst.append("Timor-Leste");
    lst.append("TM");
    lst.append("Turkmenistan");
    lst.append("TN");
    lst.append("Tunisia");
    lst.append("TO");
    lst.append("Tonga");
    lst.append("TR");
    lst.append("Turkey");
    lst.append("TT");
    lst.append("Trinidad and Tobago");
    lst.append("TV");
    lst.append("Tuvalu");
    lst.append("TW");
    lst.append("Taiwan");
    lst.append("TZ");
    lst.append("Tanzania");
    lst.append("UA");
    lst.append("Ukraine");
    lst.append("UG");
    lst.append("Uganda");
    lst.append("UM");
    lst.append("United States Minor Outlying Islands");
    lst.append("US");
    lst.append("United States");
    lst.append("UY");
    lst.append("Uruguay");
    lst.append("UZ");
    lst.append("Uzbekistan");
    lst.append("VA");
    lst.append("Holy See (Vatican City State)");
    lst.append("VC");
    lst.append("Saint Vincent and the Grenadines");
    lst.append("VE");
    lst.append("Venezuela");
    lst.append("VG");
    lst.append("Virgin Islands (GB)");
    lst.append("VI");
    lst.append("Virgin Islands (US)");
    lst.append("VN");
    lst.append("Vietnam");
    lst.append("VU");
    lst.append("Vanuatu");
    lst.append("WF");
    lst.append("Wallis and Futuna");
    lst.append("WS");
    lst.append("Samoa");
    lst.append("YE");
    lst.append("Yemen");
    lst.append("YT");
    lst.append("Mayotte");
    lst.append("ZA");
    lst.append("South Africa");
    lst.append("ZM");
    lst.append("Zambia");
    lst.append("ZW");
    lst.append("Zimbabwe");
}

Translator::~Translator(){}

QString Translator::GetCountryISO(QString &country, bool toiso){


            if (toiso)
            {
                for (int i = 1; i < lst.size(); i += 2)
                {
                    if (lst[i].toLower() == country.toLower()) return lst[i - 1];
                }
            }
            else
            {
                for (int i = 0; i < lst.size(); i += 2)
                {
                    if (lst[i].toLower() == country.toLower()) return lst[i + 1];
                }
            }

        return "";
}
