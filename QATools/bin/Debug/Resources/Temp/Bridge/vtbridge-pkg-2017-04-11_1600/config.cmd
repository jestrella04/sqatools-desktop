@echo off
cls
title VTBridge
set L=lib\
set CP=%L%comm.jar
set CP=%CP%;%L%jai-codec-1.1.3.jar
set CP=%CP%;%L%flex-messaging-common.jar
set CP=%CP%;%L%flex-messaging-core.jar
set CP=%CP%;%L%jcl_editor.jar
set CP=%CP%;%L%xml-apis.jar
set CP=%CP%;%L%castor.jar
set CP=%CP%;%L%xerces.jar
set CP=%CP%;%L%log4j-1.2.14.jar
set CP=%CP%;%L%dom.jar
set CP=%CP%;%L%jcl.jar
set CP=%CP%;%L%jgl3.1.0.jar
set CP=%CP%;%L%sax.jar
set CP=%CP%;%L%HyperJavaPOS.jar
set CP=%CP%;%L%gson-2.2.2.jar
set CP=%CP%;%L%ijpos113.jar
set CP=%CP%;%L%ijpos113_ext.jar
set CP=%CP%;%L%xercesImpl.jar
set CP=%CP%;%L%vfjpos_dist.jar
set CP=%CP%;%L%ijpos113_eft.jar
set CP=%CP%;%L%ijpos113_svcs_sun.jar
set CP=%CP%;%L%merapi.jar
set CP=%CP%;%L%vtbridge.jar
set CP=%CP%;%L%pp795se_service_object.jar
set CP=%CP%;%L%jpos.jar
set CP=%CP%;%L%gson-2.2.2.jar
set CP=%CP%;%L%RBA_SDK.jar
set CP=%CP%;%L%epson.jar
set CP=%CP%;%L%rdm.jar
set CP=%CP%;%L%com4j.jar
set CP=%CP%;%L%jna-4.1.0.jar
set CP=%CP%;%L%jna-platform-4.1.0.jar

set JAVA=C:\Program Files (x86)\Java\jdk1.8.0_31\jre\bin\
set DBG_OPTIONS=
rem set DBG_OPTIONS=-Xdebug -Xrunjdwp:transport=dt_socket,address=8001,server=y

"%JAVA%java" %DBG_OPTIONS% -cp %CP% com.cinet.virtualterminal.bridge.VirtualTerminalBridge config