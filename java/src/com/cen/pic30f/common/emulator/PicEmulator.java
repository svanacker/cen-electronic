/*
 * $Id$
 * Ce fichier est confidentiel. Il est la propriété de :
 * Oalia SA
 * 38 Boulevard Henri Sellier
 * 92150 Suresnes, France
 * Tous droits réservés.
 */
package com.cen.pic30f.common.emulator;

import java.io.IOException;

/**
 * Classe permettant de simuler le fonctionnement de serial.c et serialUtils.h
 */
public class PicEmulator {

    public int sendDec(long value) {
        String s = String.valueOf(value);
        System.out.print(s);
        int length = s.length();
        return length;
    }
    
    public int sendDecf(float value) {
        String s = String.valueOf(value);
        System.out.print(s);
        int length = s.length();
        return length;
    }

    public void openSerial(long baudRate) {
        // ne fait rien
    }

    public void closeSerial() {
        // ne fait rien
    }

    public void putString(String s) {
        System.out.print(s);
    }

    public int kbhit() {
        try {
            return System.in.read();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return -1;
    }

    public void putc(char c) {
        System.out.print(c);
    }

    public char getc() {
        // TODO : Implementation
        return ' ';
    }

    public void println() {
        System.out.println();
    }

    // Math functions

    public float sqrt(float value) {
        return (float) Math.sqrt(value);
    }

    public float atan2f(float param0, float param1) {
        return (float) Math.atan2(param0, param1);
    }

}
