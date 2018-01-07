#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Sun Jan  7 11:42:20 2018

@author: maximelefebvre
"""

# We needed to transform the csv file in order to prepare it to be used by the C++ program

import pandas as pd
import datetime as dt

df = pd.read_csv("SPX500.csv",sep=",")

df['Date - datetime'] = pd.to_datetime(df['Date'], errors='coerce')

df = df[(df["Date - datetime"] >= dt.datetime(2016,6,30).date()) & (df["Date - datetime"] <= dt.datetime(2017,6,29).date())]

columns_to_keep = ["Open","High","Low","Close","Adj Close"]

df = df[columns_to_keep] #In the C++, we will keep the "Adj Close" column

df.to_csv('SPX500-python_transformed.csv', header=False)