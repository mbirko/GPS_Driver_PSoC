# GPS_Driver_PSoC

This is an abselut mess of a development that went... fairly well? 

I was in change of creating a GPS Driver, that was to be used for navigation for an Unmanned Boat, that was to collect messuremnt in lakes. 

I spend alot of time reworking logic in the Research folder, 
Where my past poor understading of design pattern, testing and genneral software tools, lead me to build my own weird tests. 

The GPS modul sent out strings with I2C, witch the module then recived and should anaylise. 
To speed up development, i created a I2C Simulated, that just spit out hte same kind of tests in the stdout, 
and the I2C mock class could then input that to the accutal logic. 

This is deffently not the way to do it. 
But it ment that i could qucily review and determin if my parser acttually recived and converted the recived informaton correctly. 
Almost Test Driven Development. 

Agian, its not pretty. It does only handle succes. 
But the expirence of hacking this togehter in a very sort time was fun. 

Once it worked in the test enviorment(if you can call it that), porting it to the PSoC was a matter of trying to make all print and test work with UART. 
I tried making it easy to switch over with a flag and IFDEF's. 
And only had limmited succes. 
Eventtually, i did get a working driver, that, when calibareted, could give locations. 



## The project it belongs to

I dont have permestion to share the rest of the projects code. 

