# -*- coding: utf-8 -*-
"""
Created on Sun Feb 16 16:28:31 2020

@author: Barkha Bharti

Operating Systems Assignment: Page Replacement Techniques
"""
import sys

#----Implementing LRU Algorithm ------------------
def lru(no_of_frames, no_of_pages, pages):
    print("----------LRU Algorithm-----------\n")
    page_fault = 0
    frames = [-1] * no_of_frames
    f_count = 0  
    recent_frames = {}   
    for p in range(len(pages)):
        if pages[p] not in recent_frames.keys():
            recent_frames[pages[p]] = p
        if pages[p] not in frames:
            page_fault += 1
            if f_count < no_of_frames:
              frames[f_count] = pages[p]
              f_count += 1
            else:
                least_recent = [k for k, v in recent_frames.items() if v == min(recent_frames[x] for x in frames)]
                index = frames.index(least_recent[0])
                frames[index] = pages[p]
        recent_frames[pages[p]] = p
        for f in frames:
                print(f, end = " ")
        print('\n')
        
    print("Total page faults: ", page_fault) 

#----Implementing FIFO Algorithm ------------------    
def fifo(no_of_frames, no_of_pages, pages):
    print("----------FIFO Algorithm-----------\n")
    frames = [-1] * no_of_frames
    current = 0
    page_fault = 0
  
    for p in pages:
        if p not in frames:
            frames[current] = p
            current = (current + 1) % no_of_frames
            page_fault += 1
        for f in frames:
            print(f, end = " ")
        print('\n')
    print("Total page faults: ", page_fault)
                 
#----Implementing LFU Algorithm -------------------
def lfu(no_of_frames, no_of_pages, pages):
    print("----------LFU Algorithm-----------\n")
    page_fault = 0
    frame_counter = 0
    frames = [-1] * no_of_frames
    page_freq = {}
    for p in range(len(pages)):
        if pages[p] not in page_freq.keys():
            page_freq[pages[p]] = [0, -1]
        if pages[p] not in frames:
            page_freq[pages[p]][1]  = p
            page_fault += 1
            if frame_counter < no_of_frames:
                frames[frame_counter] = pages[p]
                frame_counter += 1
            else:
                res = [k for k, v in page_freq.items() if v[0] == min(page_freq[x][0] for x in frames)]
                res = list(set(res) & set(frames))
                if(len(res) > 1):
                    fres = [k for k, v in page_freq.items() if v[1] == min(page_freq[x][1] for x in res)]
                    fres = list(set(fres) & set(frames))
                    k = fres[0]
                else:
                    k = res[0]
                index = frames.index(k)
                frames[index] = pages[p]
                page_freq[k][0] = 0
        for f in frames:
            print(f, end = " ")
        print('\n')
        page_freq[pages[p]][0] += 1
        
    print("Total page faults: ", page_fault)      
      
def main():
    """"---------opening the file--------------------------------------"""
    try:
        argc = len(sys.argv) - 1
        with open(sys.argv[1]) as f:
            no_of_pages, no_of_frames = [int(x) for x in next(f).split()] # read first line
            pages = [[int(x) for x in line.split()] for line in f][0]
        try:
            if argc == 1 or argc == 4:
                fifo(no_of_frames, no_of_pages, pages)
                lfu(no_of_frames, no_of_pages, pages)
                lru(no_of_frames, no_of_pages, pages)
                
            elif argc == 2:
                if sys.argv[2] == "ff":
                    fifo(no_of_frames, no_of_pages, pages)
                elif sys.argv[2] == "lr":
                    lru(no_of_frames, no_of_pages, pages)
                elif sys.argv[2] == "lf":
                    lfu(no_of_frames, no_of_pages, pages)
            elif argc == 3:
                if (sys.argv[2] == "ff" and sys.argv[3] == "lr") or (sys.argv[3] == "ff" and sys.argv[2] == "lr"):
                    fifo(no_of_frames, no_of_pages, pages)
                    lru(no_of_frames, no_of_pages, pages)
                elif (sys.argv[2] == "ff" and sys.argv[3] == "lf") or (sys.argv[3] == "ff" and sys.argv[2] == "lf"):
                    fifo(no_of_frames, no_of_pages, pages)
                    lfu(no_of_frames, no_of_pages, pages)
                elif (sys.argv[2] == "lf" and sys.argv[3] == "lr") or (sys.argv[3] == "lf" and sys.argv[2] == "lr"):
                    lru(no_of_frames, no_of_pages, pages)
                    lfu(no_of_frames, no_of_pages, pages)
            
        finally:
            f.close()   #Closing the file
    except IndexError:
        print("Please enter input file name.")
    except FileNotFoundError:
        print("Input File doesn't exist.")
  
if __name__== "__main__":
  main()