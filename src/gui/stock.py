import urllib.request
import json
class GoogleFinanceAPI:
        def __init__(self):
            self.prefix = "https://www.worldtradingdata.com/api/v1/stock?symbol=AAPL,MSFT,HSBA.L&api_token=TTDVoItRUyorTJljdu95aO2kDEiu7Py3TKcsHNdG2U16Sm11m9Mrkg01e7C3"
        
        def get(self,symbol,exchange):
            url = self.prefix+"%s:%s"%(exchange,symbol)
            u = urllib.request.urlopen(url)
            content = u.read().decode('utf-8')
            obj = json.loads(content[3:])
            return obj[0]
            
            
if __name__ == "__main__":
        c = GoogleFinanceAPI()
        quote = c.get("RELIANCE","NSE")
        print(quote)
