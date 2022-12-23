em="SIC GCBSPNA XPMHACQ JB GPYXSMEPNXIY JR SINS MF SPNBRQJSSJBE JBFMPQNSJMB FPMQ N XMJBS N SM N XMJBS H HY QCNBR MF N XMRRJHAY JBRCGZPC GINBBCA JB RZGI N VNY SINS SIC MPJEJBNA QCRRNEC GNB MBAY HC PCGMTCPCD HY SIC PJEISFZA PCGJXJCBSR SIC XNPSJGJXNBSR JB SIC SPNBRNGSJMB NPC NAJGC SIC MPJEJBNSMP MF SIC QCRRNEC HMH SIC PCGCJTCP NBD MRGNP N XMRRJHAC MXXMBCBS VIM VJRICR SM ENJB ZBNZSIMPJOCD GMBSPMA MF SIC QCRRNEC"
ch="ABCDEFGHIJKLMNOPQRSTUVWXYZ"
p={}

for i in ch:
    p[i]=round(em.count(i)/len(em),4)
p=sorted(p.items(),key=lambda x:(x[1],x[0]),reverse=True)
print(p)
table={}

table["A"]="l"
table["B"]="n"
table["C"]="e"
table["E"]="g"
table["G"]="c"
table["H"]="b"
table["I"]='h'
table["J"]='i'
table["M"]="o"
table["N"]="a"
table["O"]="z"
table["P"]="r"
table["Q"]="m"
table["R"]="s"
table["S"]="t"
table["T"]="v"
table["V"]="w"
table["X"]="p"
table["Z"]="u"
res=""
for i in em:
    if i in table.keys():
        res+=table[i]
    else:
        res+=i
print(table)
print(res)