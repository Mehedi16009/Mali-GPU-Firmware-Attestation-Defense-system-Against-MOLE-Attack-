# 🛡️ FAARM: Firmware Attestation and Authentication Framework for Mali GPUs
Firmware Attestation Defense System Against MOLE Attacks
A lightweight software prototype demonstrating how cryptographic attestation at the EL3 boundary can block malicious firmware on Mali GPU MCUs.
----
# 📌 Overview
FAARM is a prototype defense framework that protects Mali GPU Trusted Execution Environments (TEEs) from MOLE-style firmware injection attacks.
MOLE exploits a critical gap during GPU initialization, where the untrusted EL1 kernel loads MCU firmware without any integrity verification. By injecting malicious firmware, an attacker can bypass memory protections, exfiltrate sensitive data (>40 MB/s), and tamper with inference outputs, all while remaining stealthy.
FAARM closes this gap by adding cryptographic firmware signing and attestation at the EL3 secure monitor, ensuring that only vendor-authorized firmware is ever executed.
This prototype is implemented entirely in Google Colab, using Python and C/OpenSSL to emulate the signing, verification, and secure loading process.
---
# 🎯 Goals
🔐 Prevent pre-verification firmware injection by authenticating firmware before loading.
⏱ Block TOCTOU (time-of-check-to-time-of-use) tampering by locking firmware post-verification.
⚡ Achieve this with minimal performance impact — our prototype verified firmware in ~1.6 ms.
🧠 Provide a reproducible, software-only framework for researchers and students without requiring GPU hardware access.

## 🧩 Components
| File                                           | Description                                                    |
| ---------------------------------------------- | -------------------------------------------------------------- |
| `Firmware_Attestation_MaliGPU_Prototype.ipynb` | Main Google Colab notebook (step-by-step defense workflow).    |
| `firmware_signer.py`                           | Signs a firmware binary using ECDSA private key (vendor-side). |
| `firmware_verifier.c`                          | C/OpenSSL verifier run at EL3 to authenticate firmware.        |
| `firmware_loader.py`                           | Simulates EL1→EL3 firmware loading path (Linux/TEE).           |
| `firmware.bin` / `firmware.sig`                | Dummy firmware and its signature for testing.                  |
| `mcu_priv.pem` / `mcu_pub.pem`                 | Vendor signing keypair (simulated).                            |


## 🔄 FAARM Workflow
Vendor (Offline)                Device (EL3 + EL1)
-----------------               -----------------------------
1. Generate ECDSA keypair
2. Sign firmware.bin  --------> 3. EL1 sends firmware + sig → EL3
                                4. EL3 verifies signature
                                5. If valid → firmware locked
                                6. If invalid → firmware rejected
                                7. TOCTOU overwrite attempts blocked


## 📊 Demo Output
✅ Before FAARM: EL1 can load tampered firmware → MOLE attack succeeds
✅ With FAARM: EL3 rejects unsigned firmware, locks MCU → MOLE blocked

## 📊 Evaluation Results
| Test                     | Description                       | Outcome                                             |
| ------------------------ | --------------------------------- | --------------------------------------------------- |
| **Test 1**               | Overwrite before EL3 verification | ❌ Signature verification failed — firmware rejected |
| **Test 2**               | Overwrite after EL3 verification  | ❌ EL3 denied overwrite — firmware locked            |
| **Verification Latency** | Time for EL3 signature check      | **~1.56 ms**                                        |
| **Secure Memory**        | Post-verification placement       | ✅ Placed plaintext into protected region            |

FAARM successfully prevents both pre-verification injection and TOCTOU overwrite attacks, demonstrating the feasibility of this defense with negligible overhead.
-----
## 🚀 How to Run (in Google Colab)
Open Firmware_Attestation_MaliGPU_Prototype.ipynb in Google Colab.
Execute the notebook cells step by step:
🔧 Environment setup
📝 Dummy firmware creation
🔑 Key generation & signing
🧠 Signature verification (C/OpenSSL)
🧰 Secure firmware loading simulation
💥 Attack scenario (tamper + fail)
Observe the attestation workflow and verification outcomes directly.
💡 Works on any system (e.g., Mac M1) because it runs fully in the cloud.
-----
## 📚 Research Context
Inspired by MOLE (CCS 2025) — the first practical attack on GPU TEEs exploiting MCU firmware loading.
FAARM proposes a defense mechanism compatible with current Mali GPU SoCs, adding a missing attestation layer between EL1 and EL3.
The approach mirrors secure boot principles used in CPU TEEs, adapted to the GPU-MCU attack surface.

---
# 🧭 Future Work
🔄 Integrating anti-rollback versioning and remote attestation.
🧠 Extending FAARM to real Mali development boards (e.g., RK3588).
📡 Exploring secure key storage via ARM TrustZone / OP-TEE.
📑 Submitting results to a top-tier ACM/IEEE security journal.
---
# 🏷️ Keywords
Mali GPU • Firmware Attestation • TEE Security • MOLE Attack • EL3 Verification • Firmware Signing • Google Colab Prototype • Hardware-Software Co-design
---
#📝 Citation (coming soon)
Md. Mehedi Hasan et al.,
“FAARM: Firmware Attestation and Authentication Framework for Mali GPUs,”
(Under Submission), 2025.
---
👤 **Author**  
Md. Mehedi Hasan  
Prospective Ph.D. Student | Cybersecurity, LLMs, and GPU Security Research  
Email: [mehedi.hasan.ict@mbstu.ac.bd](mehedi.hasan.ict@mbstu.ac.bd)
Portfolio: [Link](https://md-mehedi-hasan-resume.vercel.app/)
