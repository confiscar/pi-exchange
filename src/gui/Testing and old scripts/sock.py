import ROOT
import pickle
import socket

HOST = 'localhost'    # The remote host
PORT = 32768          # The same port as used by the server
pickleSep = ':::::'

# =========================
# Initialize the ROOT plots 
# =========================
cc = ROOT.TCanvas('cc','Apollo Plots', 960, 720)
ROOT.SetOwnership(cc, False)
pad1 = ROOT.TPad("test_name","test_title", 0.3, 0.3, 0.8, 0.8)
pad1.Draw()
pad1.cd()
ROOT.SetOwnership(pad1, False)
g1 = ROOT.TGraph()
pad1.cd()
g1.Draw("alp")

# ==============================
# Set up the socket connection
# ==============================
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect( (HOST,PORT) )

# ====================
# Handle incoming data
# ====================
while True:
    pickled_data = s.recv(4096)
    pickled_data = pickled_data.split(pickleSep)
    ROOT.gSystem.ProcessEvents()
    for each in pickled_data:
        if len(each) > 0:
            data = pickle.loads(each)
            print ("data = "), data
            if data[0] == 'testing':
                vals = data[1]
                g1.SetPoint(vals[0], vals[1], vals[2])
                pad1.Modified()
                cc.Update()


ROOT.gApplication.Run()