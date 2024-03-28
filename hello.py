#!/usr/bin/env python
# -*- coding: utf-8 -*-

#import numpy


# -*- coding: utf-8 -*-
import numpy
import pywt
from scipy import signal
from scipy import constants
from scipy import ndimage


def hellonumpy():
        print("numpy version :",np.__version__)

def hello():
    print("hello python!")

def test_add(a, b):
        c = a + b
        print( a, "+", b," = ",c)
        return c


def filter1(data):
    data_coil1 = np.ones(40)
    data_coil2 = np.ones(40)
    data_hall1 = np.ones(40)
    data_hall2 = np.ones(40)
    for i in range(0,len(data_coil1)):
        data_coil1[i] = data[4*i]
        data_coil2[i] = data[4*i + 1]
        data_hall1[i] = data[4*i + 2]
        data_hall2[i] = data[4*i + 3]
    wn = 2 * 500 / 9900
    b, a = signal.butter(1, wn, 'low')
    data1_coil1 = signal.filtfilt(b, a, data_coil1)
    data1_coil2 = signal.filtfilt(b, a, data_coil2)
    data1_hall1 = signal.filtfilt(b, a, data_hall1)
    data1_hall2 = signal.filtfilt(b, a, data_hall2)
    data2_coil1 = np.ones(len(data1_coil1))
    data2_coil2 = np.ones(len(data1_coil2))
    data2_hall1 = np.ones(len(data1_hall1))
    data2_hall2 = np.ones(len(data1_hall2))
    w = pywt.wavedec(data1_coil1, 'db4', level=8)
    N = len(data1_coil1)
    for i in range(1, len(w)):
        thr = (np.median(np.abs(w[i])) / 0.6745) * (0.3936 + 0.1829 * (np.log(N) / np.log(2)))
        w[i] = pywt.threshold(w[i], thr, mode='soft')
    data2_coil1 = pywt.waverec(w, 'db4')
    w = pywt.wavedec(data1_coil2, 'db4', level=8)
    N = len(data1_coil2)
    for i in range(1, len(w)):
        thr = (np.median(np.abs(w[i])) / 0.6745) * (0.3936 + 0.1829 * (np.log(N) / np.log(2)))
        w[i] = pywt.threshold(w[i], thr, mode='soft')
    data2_coil2 = pywt.waverec(w, 'db4')
    w = pywt.wavedec(data1_hall1, 'db4', level=8)
    N = len(data1_hall1)
    for i in range(1, len(w)):
        thr = (np.median(np.abs(w[i])) / 0.6745) * (0.3936 + 0.1829 * (np.log(N) / np.log(2)))
        w[i] = pywt.threshold(w[i], thr, mode='soft')
    data2_hall1 = pywt.waverec(w, 'db4')
    w = pywt.wavedec(data1_hall2, 'db4', level=8)
    N = len(data1_hall2)
    for i in range(1, len(w)):
        thr = (np.median(np.abs(w[i])) / 0.6745) * (0.3936 + 0.1829 * (np.log(N) / np.log(2)))
        w[i] = pywt.threshold(w[i], thr, mode='soft')
    data2_hall2 = pywt.waverec(w, 'db4')
    data3_coil1 = np.ones(len(data2_coil1))
    data3_coil2 = np.ones(len(data2_coil2))
    data3_hall1 = np.ones(len(data2_hall1))
    data3_hall2 = np.ones(len(data2_hall2))
    data3_coil1 = signal.detrend(data2_coil1, axis=-1, type='linear', bp=0, overwrite_data=False)
    data3_coil2 = signal.detrend(data2_coil2, axis=-1, type='linear', bp=0, overwrite_data=False)
    data3_hall1 = signal.detrend(data2_hall1, axis=-1, type='linear', bp=0, overwrite_data=False)
    data3_hall2 = signal.detrend(data2_hall2, axis=-1, type='linear', bp=0, overwrite_data=False)
    N2_coil1 = len(data3_coil1)
    N2_coil2 = len(data3_coil2)
    N2_hall1 = len(data3_hall1)
    N2_hall2 = len(data3_hall2)
    data5_coil1 = np.ones(N2_coil1)
    data5_coil2 = np.ones(N2_coil2)
    data5_hall1 = np.ones(N2_hall1)
    data5_hall2 = np.ones(N2_hall2)
    ans_coil1 = data3_coil1[N2_coil1 - 1]
    ans_coil2 = data3_coil2[N2_coil2 - 1]
    ans_hall1 = data3_hall1[N2_hall1 - 1]
    ans_hall2 = data3_hall2[N2_hall2 - 1]
    data4_coil1 = np.append(data3_coil1, ans_coil1)
    data4_coil2 = np.append(data3_coil2, ans_coil2)
    data4_hall1 = np.append(data3_hall1, ans_hall1)
    data4_hall2 = np.append(data3_hall2, ans_hall2)
    for i in range(N2_coil1):
        data5_coil1[i] = data4_coil1[i] * (data4_coil1[i] - data4_coil1[i + 1])
    for i in range(N2_coil2):
        data5_coil2[i] = data4_coil2[i] * (data4_coil2[i] - data4_coil2[i + 1])
    for i in range(N2_hall1):
        data5_hall1[i] = data4_hall1[i] * (data4_hall1[i] - data4_hall1[i + 1])
    for i in range(N2_hall2):
        data5_hall2[i] = data4_hall2[i] * (data4_hall2[i] - data4_hall2[i + 1])
    data6_coil1 = np.ones(len(data5_coil1))
    data6_coil2 = np.ones(len(data5_coil2))
    data6_hall1 = np.ones(len(data5_hall1))
    data6_hall2 = np.ones(len(data5_hall2))
    wn = 2 * 500 / 9900
    b, a = signal.butter(1, wn, 'low')
    data6_coil1 = signal.filtfilt(b, a, data5_coil1)
    data6_coil2 = signal.filtfilt(b, a, data5_coil2)
    data6_hall1 = signal.filtfilt(b, a, data5_hall1)
    data6_hall2 = signal.filtfilt(b, a, data5_hall2)
    data7_coil1 = abs(signal.hilbert(data6_coil1))
    data7_coil2 = abs(signal.hilbert(data6_coil2))
    data7_hall1 = abs(signal.hilbert(data6_hall1))
    data7_hall2 = abs(signal.hilbert(data6_hall2))
    data8_coil1 = ndimage.gaussian_filter(data7_coil1, sigma=5)
    data8_coil2 = ndimage.gaussian_filter(data7_coil2, sigma=5)
    data8_hall1 = ndimage.gaussian_filter(data7_hall1, sigma=5)
    data8_hall2 = ndimage.gaussian_filter(data7_hall2, sigma=5)
    data8=np.ones(len(data8_coil1)+len(data8_coil2)+len(data8_hall1)+len(data8_hall2))
    for i in range(0,len(data8_coil1)):
        data8[4*i] = data8_coil1[i]
        data8[4*i+1] = data8_coil2[i]
        data8[4*i+2] = data8_hall1[i]
        data8[4*i+3] = data8_hall2[i]
    # data9=  np.array(data8);
    data9=list(map(int, data8))
    for i in range(1,len(data8))
        print(data8[i])
    return data9

def szTest(List):
    print (List)

    IntegerList = [1, 2, 3]
    return IntegerList

def filter2(data):
#    print("hello python!");

    data1 = numpy.ones((len(data)))
    wn = 2 * 500 / 9900
    print(constants.acre)
    b,a = signal.butter(1, wn, 'lowpass')
    data1 = signal.filtfilt(b, a, data)
    data2 = numpy.ones(len(data1))
    w = pywt.wavedec(data, 'db4', level=8)
    N = len(data1)
    for i in range(1, len(w)):
        thr = (numpy.median(numpy.abs(w[i])) / 0.6745) * (0.3936 + 0.1829 * (numpy.log(N) / numpy.log(2)))
        w[i] = pywt.threshold(w[i], thr, mode='soft')
    data2 = pywt.waverec(w, 'db4')
    data3 = numpy.ones(len(data2))
    data3 = signal.detrend(data2, axis=-1, type='linear', bp=0, overwrite_data=False)
    N2 = len(data3)
    data5 = numpy.ones(N2)
    ans = data3[N2 - 1]
    data4 = numpy.append(data3, ans)
    for i in range(N2):
        data5[i] = data4[i] * (data4[i] - data4[i + 1])
    data6 = numpy.ones(len(data5))
    wn = 2 * 500 / 9900
    b, a = signal.butter(1, wn, 'low')
    data6 = signal.filtfilt(b, a, data5)
    data7 = abs(signal.hilbert(data6))
    data8 = ndimage.gaussian_filter(data, sigma=5)
    IntegerList = [1, 2, 3]
    data9=list(map(int, data8))
    return data9
#    return IntegerList
