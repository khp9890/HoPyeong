#-*- coding: utf-8 -*-
import requests
import sys
def spider():
	pass
def main():
    url = ""
    print (sys.argv[1])
    try:
        url = sys.argv[1]
    except:
	    sys.exit(1)

    source_code = requests.get(url)
    print (source_code.text)

main()