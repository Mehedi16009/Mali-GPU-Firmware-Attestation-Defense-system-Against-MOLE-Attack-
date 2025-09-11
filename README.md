# Mali-GPU-Firmware-Attestation-Defense-system-Against-MOLE-Attack-
Prototype implementation of firmware attestation for Mali GPU MCUs — demonstrates how cryptographic signing and verification can block MOLE-style attacks by rejecting tampered firmware before execution. Built as a software-only demo in Google Colab using Python + OpenSSL. I named this defense simulation as FAAMA (Firmware Attestation Against MOLE Attack)
----
# 🔐 Mali GPU Firmware Attestation Prototype

This repository contains a **software-only prototype** of *Firmware Attestation* —  
a defense mechanism against **MOLE-style attacks** on Mali GPUs, where an attacker replaces the GPU MCU firmware with malicious code.

## 🎯 Objective
Demonstrate how cryptographic signing and verification can ensure that only **authentic, untampered firmware** is loaded into the GPU MCU.  
This closes the key security gap exploited by MOLE: **unverified `/lib/firmware` loads**.

## 🧩 Components
- `Firmware_Attestation_MaliGPU_Prototype.ipynb` — Colab notebook (step-by-step demo).
- `firmware_signer.py` — Signs a firmware binary with an ECDSA private key.
- `firmware_verifier.c` — Verifies firmware integrity/signature using a public key (compiled with OpenSSL).
- `firmware_loader.py` — Simulates Linux/TEE loader: only loads firmware if verification succeeds.
- Example artifacts:
  - `firmware.bin` (dummy binary)
  - `firmware.sig` (signature)
  - `mcu_priv.pem`, `mcu_pub.pem` (signing keys)

## 🔄 Workflow
1. Generate ECDSA keypair (vendor private key + public verification key).
2. Create a dummy `firmware.bin` (simulated GPU MCU firmware).
3. Sign the firmware → produce `firmware.sig`.
4. Verify the signature using `firmware_verifier.c`.
5. Simulate secure firmware loading in `firmware_loader.py`.
6. Tamper with the firmware → demonstrate rejection.

## 📊 Demo Output
- **Valid firmware** → Verification: OK ✅ → Firmware loaded.
- **Tampered firmware** → Verification: FAILED ❌ → Load rejected.

## 🚀 How to Run (in Google Colab)
1. Open `Firmware_Attestation_MaliGPU_Prototype.ipynb` in Google Colab.  
2. Run cells step-by-step:
   - Environment setup
   - Firmware creation
   - Key generation & signing
   - Verification
   - Loader simulation
   - Attack test (tamper + fail)  
3. Observe verification outcomes directly in Colab outputs.

## ⚠️ Security Notes
- In this demo, the public key is stored as a file.  
  ➡️ In real deployment, it must reside in **secure world hardware** (e.g., ARM TrustZone/OP-TEE, TPM).  
- Anti-rollback (versioning) and remote attestation are additional features to integrate in production.

## 📚 Research Context
This prototype is inspired by **Mole (CCS 2025)**, a GPU TEE attack exploiting MCU firmware loading weaknesses.  
By requiring attested firmware, the entry point exploited by Mole is closed with negligible performance overhead.

---

👤 **Author**  
Md. Mehedi Hasan  
Prospective Ph.D. Student | Cybersecurity, LLMs, and GPU Security Research  
Email: [mehedi.hasan.ict@mbstu.ac.bd](mehedi.hasan.ict@mbstu.ac.bd)
Portfolio: [Link](https://md-mehedi-hasan-resume.vercel.app/)
