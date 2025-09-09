#include "messageqeue.h"
#include "mainwindow.h"
#include "tuxlerapp.h"

MessageQeue::MessageQeue()
{

	msgLst << "IP_CHANGED_SUCCESSFULLY" <<
		"IP_CHANGED_SUCCESSFULLY_ALREADY_USING" <<
		"IP_NOT_CHANGED_OVERLOADED" <<
		"IP_CHANGED_FAILED_FREE" <<
		"IP_NOT_CHANGED_LIMITS" <<
		"IP_NOT_CHANGED_NOT_AVAILABLE" <<
		"IP_BECAME_UNAVAILABLE_AND_YOU_HAVE_REACHED_LIMITS" <<
		"IP_BECAME_UNAVAILABLE" <<
		"IPLISTJSON" <<
		"YOUR_IP" <<
		"SHOW_MESSAGE" <<
		"SHOW_MESSAGE1" <<
		"LOGIN_FINISHED" <<
		"WELCOME_TO_PREMIUM" <<
		"BANNED_MESSAGE" <<
		"BANNED_MESSAGE2" <<
		"USER_AGENT" <<
		"RECEIVED_ACCOUNT_INFO" <<
		"PREMIUM_INFO" <<
		"LIMITS_INFO" <<
		"ACCOUNT_INFO" <<
		"FREE_TIME_LEFT" <<
		"IP_CHANGED_SUCCESSFULLY_NEW";
}


void MessageQeue::NewMessage(){

	Lock();

    Msg m;

    if(__msgs.size() > 0) {

        m = __msgs[0];
        __msgs.removeFirst();
    }

    UnLock();

    bool UnAvail = false;

    int opt = msgLst.indexOf(m.msg);

    if(opt != -1){

        emit MainWindow::__instance->SendNewGuiEvent(QString("<message>SETCURSOR</message><details>cursor:default !important</details>"));

        switch(opt){

		case 21:
		{
			MainWindow::__instance->FreePremiumTime(m.det);
		}
		break;

		case 20:
		{
			MainWindow::__instance->AccountInfo(m.det);
		}
		break;

		case 19:
		{
			MainWindow::__instance->LimitsInfo(m.det);
		}
		break;

		case 18:
		{
            MainWindow::__instance->ExpireInfo(m.det);
		}
		break;

        case 17:
        {
            QString p = getTag("passok", m.det);
            QString pr = getTag("premium", m.det);
            QString e = getTag("email", m.det);
            QString pass = getTag("password", m.det);

            MainWindow::__instance->ReceivedAccountInfo(e, pass, p == "1" ? true : false, pr == "1" ? true : false);
        }
        break;

        case 16:
{
            QJsonDocument jsonResponse = QJsonDocument::fromJson(m.det.toUtf8());

            QJsonObject jsonObject = jsonResponse.object();

            QString value = jsonObject.value(QString("userAgent")).toString();
}
            break;

        case 13://"WELCOME_TO_PREMIUM"

            MainWindow::__instance->__isPremiumset(true);

            break;
        case 12:

            MainWindow::__instance->__isPremiumset(false);

            break;
        case 10://SHOW_MESSAGE

			if(m.det.indexOf("<type>WELCOME_TO_PREMIUM</type>") == 0)
				MainWindow::__instance->__isPremiumset(true);

			if(m.det.indexOf("<type>PREMIUM_EXPIRED</type>") == 0)
				MainWindow::__instance->__isPremiumset(false);

            listmsg.push_back("<message>SHOW_MESSAGE<details>" + m.det + "</details></message>");

            break;

        case 11://SHOW_MESSAGE1

            listmsg.push_back(m.det);

            break;

        case 9://"YOUR_IP"
{
            QString re("<ip>(.*)</ip>.*<location>.*<country>(.*)</country>.*<region>(.*)</region>.*<countryiso>(.*)</countryiso>.*<city>(.*)</city>.*</location>");

            QString hisip2 = "Unknown";

            QString hiscountry = "Unknown";

            QString hiscity = "Unknown";

            QString countryiso = "";

            QString region = "Unknown";

            bool matched = false;

            QRegExp rx(re);

            rx.setMinimal(true);

            if(rx.indexIn(m.det) != -1){

                matched = true;

                hisip2 = rx.cap(1);

                hiscountry = rx.cap(2);

                hiscity = rx.cap(5);

                countryiso = rx.cap(4);

                region = rx.cap(3);
            }

            MainWindow::__instance->myIP.city = hiscity;
            MainWindow::__instance->myIP.country = hiscountry;
            MainWindow::__instance->myIP.countryiso = countryiso;
            MainWindow::__instance->myIP.ip = hisip2;
            MainWindow::__instance->myIP.regionfull = MainWindow::__instance->translator.TryGetFullRegion(region, countryiso);
            MainWindow::__instance->myIP.localid = 0;

            if(MainWindow::__instance->myIP.regionfull.length() <= 0) 
				MainWindow::__instance->myIP.regionfull = "Unknown";

            if(MainWindow::__instance->myIP.city.length() <= 0) 
				MainWindow::__instance->myIP.city = "Unknown";

            if(!MainWindow::__instance->__isIpChangingActive()) 
				MainWindow::__instance->SetMyIp(MainWindow::__instance->myIP);
}
            break;

        case 8:

            MainWindow::__instance->ipList.ParseIpList(m.det);

            MainWindow::__instance->ipList.__ipListLoaded = true;

            emit MainWindow::__instance->SendNewGuiEvent(QString("<message>ENABLEDISABLELOGINBUTTON</message><details>false</details>"));
            emit MainWindow::__instance->SendNewGuiEvent(QString("<message>ACTIVATEIPLIST</message><details>1</details>"));

            break;

		case 22://IP_CHANGED_SUCCESSFULLY_NEW

		{
			QString mtch = "<status>(.*)</status>.*<location>.*<country>(.*)</country>.*<city>(.*)</city>.*</location>.*<port>(.*)</port>";

			QRegExp rx(mtch);

			rx.setMinimal(true);

			QString hiscountry = "Unknown", hiscity = "Unknown", server_port;

			bool matched = false;

			if (rx.indexIn(m.det) != -1)
			{
				matched = true;

				hiscountry = rx.cap(2);
				hiscity = rx.cap(3);
				server_port = rx.cap(4);
			}

			if (hiscity.length() <= 0) 
				hiscity = "Unknown";

			if (matched)
			{
				if (hiscity == "(null)") 
					hiscity = "Unknown";

				if (hiscountry == "(null)")
					hiscountry = "Unknown";

				bool setremote = false;

				QString hiscountryiso = MainWindow::__instance->translator.GetCountryISO(hiscountry, true);

				IPS ip;

				ip.country = hiscountry;
				ip.city = hiscity;
				ip.countryiso = hiscountryiso;

				ip.localid = server_port.toInt();

				if (MainWindow::__instance->__isIpChangingActive()) 
					MainWindow::__instance->ShowToolBarWindow(MainWindow::__instance->TuxlerInfoText, "Ip changed successfully.\\nLocation: " + hiscountry + ", " + hiscity);

				if (ip.regionfull.length() <= 0)
					ip.regionfull = "Unknown";

				if (ip.city.length() <= 0)
					ip.city = "Unknown";

				MainWindow::__instance->currentIP = ip;

				MainWindow::__instance->SetCurrentIp(ip);
			}
		}

			break;


        case 0://"IP_CHANGED_SUCCESFULLY"
{
UNAVAIL:

         bool limitsr = UnAvail;

         UnAvail = false;

         QString mtch = "<status>(.*)</status>.*<displaymessage>.*<title>(.*)</title>.*<body>(.*)</body>.*</displaymessage>.*<ip>(.*)</ip>.*<location>.*<country>(.*)</country>.*<region>(.*)</region>.*<city>(.*)</city>.*</location>.*<port>(.*)</port>";

         if(limitsr) mtch = "<status>(.*)</status>.*<displaymessage>.*<title>(.*)</title>.*<body>(.*)</body>.*</displaymessage>.*<ip>(.*)</ip>.*<location>.*<country>(.*)</country>.*<city>(.*)</city>.*</location>.*<port>(.*)</port>";

         QRegExp rx(mtch);

         rx.setMinimal(true);

         QString hisip2 = "Unknown", hiscountry = "Unknown", hiscity = "Unknown", hisregion = "Unknown";

         bool matched = false;

            if(rx.indexIn(m.det) != -1){

                 matched = true;

                 hisip2 = rx.cap(4);
                 hiscountry = rx.cap(5);

                 if(!limitsr){

                       hiscity = rx.cap(7);
                       hisregion = rx.cap(6);

                 }else  hiscity = rx.cap(6);
             }

             if(hiscity.length() <= 0) hiscity = "Unknown";

             if(matched){

                 if (hiscity == "(null)") hiscity = "Unknown";
                 if (hiscountry == "(null)") hiscountry = "Unknown";
                 if (hisregion == "(null)") hisregion = "Unknown";

                 bool setremote = false;

                 //if(MainWindow::__instance->proxy->DisableConnections != 0) setremote = true;

                 //MainWindow::__instance->proxy->DisableConnections = 0;

                 QString hiscountryiso = MainWindow::__instance->translator.GetCountryISO(hiscountry, true);

                 IPS ip;

                 ip.country = hiscountry;
                 ip.city = hiscity;
                 ip.regionfull = hisregion;
                 ip.countryiso = hiscountryiso;

                 if(MainWindow::__instance->__isIpChangingActive()) MainWindow::__instance->ShowToolBarWindow(MainWindow::__instance->TuxlerInfoText, "Ip changed successfully.\\nLocation: " + hiscountry + ", " + hiscity);

                 QString ciso = MainWindow::__instance->translator.GetCountryISO(hiscountry);

                 int portB = -1;

                     if(limitsr)
					 {
                         QString wport = rx.cap(7);

                         QString aport = (wport);

                         portB = (aport).toInt();
					 }
					 else
					 {
                         QString wport = rx.cap(8);

                         QString aport = (wport);

                         portB = (aport).toInt();
                     }

                     if(ip.regionfull.length() <= 0) 
						 ip.regionfull = "Unknown";

                     if(ip.city.length() <= 0) 
						 ip.city = "Unknown";

                     ip.localid = portB;
                     MainWindow::__instance->currentIP = ip;

					MainWindow::__instance->SetCurrentIp(ip);

                     QString statusA = rx.cap(1);

                     emit MainWindow::__instance->NewPort(portB);

                     emit MainWindow::__instance->SendNewGuiEvent(QString("<message>HIGHLIGHT</message><details>"+QString::number(portB-1)+"</details>"));
             }
}
            break;
        case 1://"IP_CHANGED_SUCCESSFULLY_ALREADY_USING"

            MainWindow::__instance->ShowToolBarWindow(MainWindow::__instance->TuxlerInfoText, "You are already using this IP.");

            break;
        case 2://"IP_NOT_CHANGED_OVERLOADED"

             MainWindow::__instance->ShowToolBarWindow(MainWindow::__instance->TuxlerInfoText, "This ip is currently overloaded.");

            break;
        case 3://"IP_CHANGED_FAILED_FREE"

            MainWindow::__instance->ShowToolBarWindow(MainWindow::__instance->TuxlerInfoText, "IP change failed. \\nThis IP is not available in free version.");

            break;
        case 4://"IP_NOT_CHANGED_LIMITS"

            MainWindow::__instance->ShowToolBarWindow(MainWindow::__instance->TuxlerInfoText, "IP not changed due to free version limits.");

            break;
        case 5://"IP_NOT_CHANGED_NOT_AVAILABLE"


            MainWindow::__instance->ShowToolBarWindow(MainWindow::__instance->TuxlerInfoText, "This ip is no longer available.");

            break;
        case 6://"IP_BECAME_UNAVAILABLE_AND_YOU_HAVE_REACHED_LIMITS"

         if(MainWindow::__instance->__isIpChangingActive()){

            MainWindow::__instance->ShowToolBarWindow(MainWindow::__instance->TuxlerInfoText, "IP You were using is now not available.\\n\\nConnections are disabled and will resume in 10 seconds and new IP address will be assigned.\\n\\nIf you want to use location specific IP please change it manually now.");

            //MainWindow::__instance->proxy->DisableConnections = time(NULL);
         }

         emit MainWindow::__instance->NewPort(MainWindow::__instance->PortIfFail);

         MainWindow::__instance->currentIP.localid = -1;

         MainWindow::__instance->SetMyIp(MainWindow::__instance->myIP);

         emit MainWindow::__instance->SendNewGuiEvent(QString("<message>HIGHLIGHT</message><details>CLEAR</details>"));

         UnAvail = true;

         goto UNAVAIL;

            break;

        case 7://"IP_BECAME_UNAVAILABLE"

         if (MainWindow::__instance->__isIpChangingActive()){

            MainWindow::__instance->ShowToolBarWindow(MainWindow::__instance->TuxlerInfoText, "IP You were using is now not available.\\n\\nConnections are disabled and will resume in 10 seconds and new IP address will be assigned.\\n\\nIf you want to use location specific IP please change it manually now.");

            //MainWindow::__instance->proxy->DisableConnections = time(NULL);
         }

            MainWindow::__instance->currentIP.localid = -1;

            MainWindow::__instance->SetMyIp(MainWindow::__instance->myIP);

            emit MainWindow::__instance->SendNewGuiEvent(QString("<message>HIGHLIGHT</message><details>CLEAR</details>"));

            break;
        }
    }
}
