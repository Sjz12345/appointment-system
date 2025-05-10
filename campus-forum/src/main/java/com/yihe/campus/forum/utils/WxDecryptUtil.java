package com.yihe.campus.forum.utils;

import org.apache.tomcat.util.codec.binary.Base64;

import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.nio.charset.StandardCharsets;
import java.security.spec.AlgorithmParameterSpec;

public class WxDecryptUtil {
    public static String decrypt(String encryptedData, String sessionKey, String iv) {
        try {
            byte[] keyBytes = Base64.decodeBase64(sessionKey);
            byte[] ivBytes = Base64.decodeBase64(iv);
            byte[] encryptedBytes = Base64.decodeBase64(encryptedData);

            SecretKeySpec keySpec = new SecretKeySpec(keyBytes, "AES");
            AlgorithmParameterSpec paramSpec = new IvParameterSpec(ivBytes);

            Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
            cipher.init(Cipher.DECRYPT_MODE, keySpec, paramSpec);
            
            return new String(cipher.doFinal(encryptedBytes), StandardCharsets.UTF_8);
        } catch (Exception e) {
            throw new RuntimeException("数据解密失败", e);
        }
    }
}