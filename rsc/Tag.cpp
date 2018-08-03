#include "Tag.h"

using namespace rsc;

std::unordered_map<uint16_t, std::wstring> const Tag::name_map_{
    { 0x0006, L"Object Identifier (OID)" },
    { 0x0041, L"Country code and national data" },
    { 0x0042, L"Issuer Identification Number (IIN)" },
    { 0x0043, L"Card service data" },
    { 0x0044, L"Initial access data" },
    { 0x0045, L"Card issuer`s data" },
    { 0x0046, L"Pre-issuing data" },
    { 0x0047, L"Card capabilities" },
    { 0x0048, L"Status information" },
    { 0x004D, L"Extended header list" },
    { 0x004F, L"Application Identifier (ADF Name)" },
    { 0x0050, L"Application Label" },
    { 0x0051, L"Path" },
    { 0x0052, L"Command to perform" },
    { 0x0053, L"Discretionary data" },
    { 0x0056, L"Track 1 Data" },
    { 0x0056, L"Track 1 Equivalent Data" },
    { 0x0057, L"Track 2 Equivalent Data" },
    { 0x0058, L"Track 3 Equivalent Data" },
    { 0x0059, L"Card expiration date" },
    { 0x005A, L"Application Primary Account Number (PAN)" },
    { 0x005B, L"Name of an individual" },
    { 0x005C, L"Tag list" },
    { 0x005D, L"Deleted (see 9D)" },
    { 0x005D, L"Header list" },
    { 0x005E, L"Proprietary login data" },
    { 0x0060, L"Template, Dynamic Authentication" },
    { 0x0061, L"Application Template / Directory Entry" },
    { 0x0062, L"File Control Parameters (FCP) Template" },
    { 0x0063, L"Wrapper" },
    { 0x0064, L"Template, File Management Data (FMD)" },
    { 0x0065, L"Cardholder related data" },
    { 0x0066, L"Template, Card data" },
    { 0x0067, L"Template, Authentication data" },
    { 0x0068, L"Special user requirements" },
    { 0x006A, L"Template, Login" },
    { 0x006B, L"Template, Qualified name" },
    { 0x006C, L"Template, Cardholder image" },
    { 0x006D, L"Template, Application image" },
    { 0x006E, L"Application related data" },
    { 0x006F, L"File Control Information (FCI) Template" },
    { 0x006F, L"Template, File Control Parameters and File Management Data (FCI)" },
    { 0x0070, L"READ RECORD Response Message Template" },
    { 0x0070, L"Template, AEF Data" },
    { 0x0071, L"Issuer Script Template 1" },
    { 0x0071, L"Template, Issuer Script 1" },
    { 0x0072, L"Issuer Script Template 2" },
    { 0x0072, L"Template, Issuer Script 2" },
    { 0x0073, L"Directory Discretionary Template" },
    { 0x0077, L"Response Message Template Format 2" },
    { 0x0077, L"Template, Response Message Format 2" },
    { 0x0078, L"Compatible Tag Allocation Authority" },
    { 0x0079, L"Coexistent Tag Allocation Authority" },
    { 0x007A, L"Template, Security Support (SS)" },
    { 0x007B, L"Template, Security Environment (SE)" },
    { 0x007D, L"Template, Secure Messaging (SM)" },
    { 0x007E, L"Template, Nesting Interindustry data objects" },
    { 0x0080, L"Response Message Template Format 1" },
    { 0x0081, L"Amount, Authorised (Binary)" },
    { 0x0082, L"Application Interchange Profile (AIP)" },
    { 0x0083, L"Command Template" },
    { 0x0084, L"Dedicated File (DF) Name" },
    { 0x0086, L"Issuer Script Command" },
    { 0x0087, L"Application Priority Indicator" },
    { 0x0088, L"Short File Identifier (SFI)" },
    { 0x0089, L"Authorisation Code" },
    { 0x0089, L"Authorization Code" },
    { 0x008A, L"Authorisation Response Code (ARC)" },
    { 0x008A, L"Authorization Response Code (ARC)" },
    { 0x008C, L"Card Risk Management Data Object List 1 (CDOL1)" },
    { 0x008D, L"Card Risk Management Data Object List 2 (CDOL2)" },
    { 0x008E, L"Cardholder Verification Method (CVM) List" },
    { 0x008F, L"Certification Authority Public Key Index (PKI)" },
    { 0x0090, L"Issuer Public Key Certificate" },
    { 0x0091, L"Issuer Authentication Data" },
    { 0x0092, L"Issuer Public Key Remainder" },
    { 0x0093, L"Signed Static Application Data (SAD)" },
    { 0x0094, L"Application File Locator (AFL)" },
    { 0x0095, L"Terminal Verification Results (TVR)" },
    { 0x0097, L"Transaction Certificate Data Object List (TDOL)" },
    { 0x0098, L"Transaction Certificate (TC) Hash Value" },
    { 0x0099, L"Transaction Personal Identification Number (PIN) Data" },
    { 0x009A, L"Transaction Date" },
    { 0x009B, L"Transaction Status Information (TSI)" },
    { 0x009C, L"Transaction Type" },
    { 0x009D, L"Directory Definition File (DDF) Name" },
    { 0x00A5, L"File Control Information (FCI) Proprietary Template" },
    { 0x5F20, L"Cardholder Name" },
    { 0x5F21, L"Track 1" },
    { 0x5F22, L"Track 2" },
    { 0x5F23, L"Track 3" },
    { 0x5F24, L"Application Expiration Date" },
    { 0x5F25, L"Application Effective Date" },
    { 0x5F26, L"Date, Card Effective" },
    { 0x5F27, L"Interchange control" },
    { 0x5F28, L"Issuer Country Code" },
    { 0x5F29, L"Interchange profile" },
    { 0x5F2A, L"Transaction Currency Code" },
    { 0x5F2B, L"Date of birth" },
    { 0x5F2C, L"Cardholder nationality" },
    { 0x5F2D, L"Language Preference" },
    { 0x5F2D, L"Language Preference" },
    { 0x5F2E, L"Cardholder biometric data" },
    { 0x5F2F, L"PIN usage policy" },
    { 0x5F30, L"Service Code" },
    { 0x5F32, L"Transaction counter" },
    { 0x5F33, L"Date, Transaction" },
    { 0x5F34, L"Application Primary Account Number (PAN) Sequence Number (PSN)" },
    { 0x5F35, L"Sex (ISO 5218)" },
    { 0x5F36, L"Transaction Currency Exponent" },
    { 0x5F37, L"Static internal authentication (one-step)" },
    { 0x5F38, L"Static internal authentication - first associated data" },
    { 0x5F39, L"Static internal authentication - second associated data" },
    { 0x5F3A, L"Dynamic internal authentication" },
    { 0x5F3B, L"Dynamic external authentication" },
    { 0x5F3C, L"Dynamic mutual authentication" },
    { 0x5F3C, L"Transaction Reference Currency Code" },
    { 0x5F3D, L"Transaction Reference Currency Exponent" },
    { 0x5F40, L"Cardholder portrait image" },
    { 0x5F41, L"Element list" },
    { 0x5F42, L"Address" },
    { 0x5F43, L"Cardholder handwritten signature image" },
    { 0x5F44, L"Application image" },
    { 0x5F45, L"Display message" },
    { 0x5F46, L"Timer" },
    { 0x5F47, L"Message reference" },
    { 0x5F48, L"Cardholder private key" },
    { 0x5F49, L"Cardholder public key" },
    { 0x5F4A, L"Public key of certification authority" },
    { 0x5F4B, L"Deprecated (see note 2 below)" },
    { 0x5F4C, L"Certificate holder authorization" },
    { 0x5F4D, L"Integrated circuit manufacturer identifier" },
    { 0x5F4E, L"Certificate content" },
    { 0x5F50, L"Issuer Uniform resource locator (URL)" },
    { 0x5F53, L"International Bank Account Number (IBAN)" },
    { 0x5F54, L"Bank Identifier Code (BIC)" },
    { 0x5F55, L"Issuer Country Code (alpha2 format)" },
    { 0x5F56, L"Issuer Country Code (alpha3 format)" },
    { 0x5F57, L"Account Type" },
    { 0x6080, L"Commitment (e.g., a positive number less than the public RSA modulus in use)" },
    { 0x6081, L"Challenge (e.g., a number, possibly zero, less than the public RSA exponent in use)" },
    { 0x6082, L"Response (e.g., a positive number less than the public RSA modulus in use)" },
    { 0x6083, L"Committed challenge (e.g., the hash-code of a commitment data object)" },
    { 0x6084, L"Authentication code (e.g., the hash-code of one or more data fields and a commitment data object)" },
    { 0x6085, L"Exponential (e.g., a public positive number for establishing a session key by a DH method)" },
    { 0x60A0, L"Template, Identification data" },
    { 0x6280, L"Number of data bytes in the file, excluding structural information" },
    { 0x6281, L"Number of data bytes in the file, including structural information if any" },
    { 0x6282, L"File descriptor byte" },
    { 0x6283, L"File identifier" },
    { 0x6284, L"DF name" },
    { 0x6285, L"Proprietary information, primitive encoding (i.e., not coded in BER-TLV)" },
    { 0x6286, L"Security attribute in proprietary format" },
    { 0x6287, L"Identifier of an EF containing an extension of the file control information" },
    { 0x6288, L"Short EF identifier" },
    { 0x628A, L"Life cycle status byte (LCS)" },
    { 0x628B, L"Security attribute referencing the expanded format" },
    { 0x628C, L"Security attribute in compact format" },
    { 0x628D, L"Identifier of an EF containing security environment templates" },
    { 0x62A0, L"Template, Security attribute for data objects" },
    { 0x62A1, L"Template, Security attribute for physical interfaces" },
    { 0x62A2, L"One or more pairs of data objects, short EF identifier (tag 88) - absolute or relative path (tag 51)" },
    { 0x62A5, L"Proprietary information, constructed encoding" },
    { 0x62AB, L"Security attribute in expanded format" },
    { 0x62AC, L"Identifier of a cryptographic mechanism" },
    { 0x6A80, L"Qualifier" },
    { 0x6A81, L"Telephone Number" },
    { 0x6A82, L"Text" },
    { 0x6A83, L"Delay indicators, for detecting an end of message" },
    { 0x6A84, L"Delay indicators, for detecting an absence of response" },
    { 0x6B06, L"Qualified name" },
    { 0x6B80, L"Name" },
    { 0x6BA0, L"Name" },
    { 0x6FA5, L"Template, FCI A5" },
    { 0x7186, L"Issuer Script Command" },
    { 0x7A80, L"Card session counter" },
    { 0x7A81, L"Session identifier" },
    { 0x7A82, L"File selection counter" },
    { 0x7A83, L"File selection counter" },
    { 0x7A84, L"File selection counter" },
    { 0x7A85, L"File selection counter" },
    { 0x7A86, L"File selection counter" },
    { 0x7A87, L"File selection counter" },
    { 0x7A88, L"File selection counter" },
    { 0x7A89, L"File selection counter" },
    { 0x7A8A, L"File selection counter" },
    { 0x7A8B, L"File selection counter" },
    { 0x7A8C, L"File selection counter" },
    { 0x7A8D, L"File selection counter" },
    { 0x7A8E, L"File selection counter" },
    { 0x7A93, L"Digital signature counter" },
    { 0x7B80, L"SEID byte, mandatory" },
    { 0x7B8A, L"LCS byte, optional" },
    { 0x7BA4, L"Control reference template (CRT)" },
    { 0x7BAA, L"Control reference template (CRT)" },
    { 0x7BAC, L"Cryptographic mechanism identifier template, optional" },
    { 0x7BB4, L"Control reference template (CRT)" },
    { 0x7BB6, L"Control reference template (CRT)" },
    { 0x7BB8, L"Control reference template (CRT)" },
    { 0x7D80, L"Plain value not coded in BER-TLV" },
    { 0x7D81, L"Plain value not coded in BER-TLV" },
    { 0x7D82, L"Cryptogram (plain value coded in BER-TLV and including secure messaging data objects)" },
    { 0x7D83, L"Cryptogram (plain value coded in BER-TLV and including secure messaging data objects)" },
    { 0x7D84, L"Cryptogram (plain value coded in BER-TLV, but not including secure messaging data objects)" },
    { 0x7D85, L"Cryptogram (plain value coded in BER-TLV, but not including secure messaging data objects)" },
    { 0x7D86, L"Padding-content indicator byte followed by cryptogram (plain value not coded in BER-TLV)" },
    { 0x7D87, L"Padding-content indicator byte followed by cryptogram (plain value not coded in BER-TLV)" },
    { 0x7D8E, L"Cryptographic checksum (at least four bytes)" },
    { 0x7D90, L"Hash-code" },
    { 0x7D91, L"Hash-code" },
    { 0x7D92, L"Certificate (not BER-TLV coded data)" },
    { 0x7D93, L"Certificate (not BER-TLV coded data)" },
    { 0x7D94, L"Security environment identifier (SEID byte, see 6.5)" },
    { 0x7D95, L"Security environment identifier (SEID byte, see 6.5)" },
    { 0x7D96, L"Number Le in the unsecured command APDU (one or two bytes)" },
    { 0x7D97, L"Number Le in the unsecured command APDU (one or two bytes)" },
    { 0x7D99, L"Processing status of the secured response APDU (new SW1-SW2, two bytes)" },
    { 0x7D9A, L"Input data element for the computation of a digital signature (the value field is signed)" },
    { 0x7D9B, L"Input data element for the computation of a digital signature (the value field is signed)" },
    { 0x7D9C, L"Public key" },
    { 0x7D9D, L"Public key" },
    { 0x7D9E, L"Digital signature" },
    { 0x7DA0, L"Input template for the computation of a hash-code (the template is hashed)" },
    { 0x7DA1, L"Input template for the computation of a hash-code (the template is hashed)" },
    { 0x7DA2, L"Input template for the verification of a cryptographic checksum (the template is integrated)" },
    { 0x7DA4, L"Control reference template for authentication (AT)" },
    { 0x7DA5, L"Control reference template for authentication (AT)" },
    { 0x7DA8, L"Input template for the verification of a digital signature (the template is signed)" },
    { 0x7DAA, L"Template, Control reference for hash-code (HT)" },
    { 0x7DAB, L"Template, Control reference for hash-code (HT)" },
    { 0x7DAC, L"Input template for the computation of a digital signature (the concatenated value fields are signed)" },
    { 0x7DAD, L"Input template for the computation of a digital signature (the concatenated value fields are signed)" },
    { 0x7DAE, L"Input template for the computation of a certificate (the concatenated value fields are certified)" },
    { 0x7DAF, L"Input template for the computation of a certificate (the concatenated value fields are certified)" },
    { 0x7DB0, L"Plain value coded in BER-TLV and including secure messaging data objects" },
    { 0x7DB1, L"Plain value coded in BER-TLV and including secure messaging data objects" },
    { 0x7DB2, L"Plain value coded in BER-TLV, but not including secure messaging data objects" },
    { 0x7DB3, L"Plain value coded in BER-TLV, but not including secure messaging data objects" },
    { 0x7DB4, L"Control reference template for cryptographic checksum (CCT)" },
    { 0x7DB5, L"Control reference template for cryptographic checksum (CCT)" },
    { 0x7DB6, L"Control reference template for digital signature (DST)" },
    { 0x7DB7, L"Control reference template for digital signature (DST)" },
    { 0x7DB8, L"Control reference template for confidentiality (CT)" },
    { 0x7DB9, L"Control reference template for confidentiality (CT)" },
    { 0x7DBA, L"Response descriptor template" },
    { 0x7DBB, L"Response descriptor template" },
    { 0x7DBC, L"Input template for the computation of a digital signature (the template is signed)" },
    { 0x7DBD, L"Input template for the computation of a digital signature (the template is signed)" },
    { 0x7DBE, L"Input template for the verification of a certificate (the template is certified)" },
    { 0x7F20, L"Display control template" },
    { 0x7F21, L"Cardholder certificate" },
    { 0x7F2E, L"Biometric data template" },
    { 0x7F49, L"Template, Cardholder public key" },
    { 0x7F4C, L"Template, Certificate Holder Authorization" },
    { 0x7F4E, L"Certificate Body" },
    { 0x7F60, L"Template, Biometric information" },
    { 0x9F01, L"Acquirer Identifier" },
    { 0x9F02, L"Amount, Authorised (Numeric)" },
    { 0x9F02, L"Authorised Amount (Numeric)" },
    { 0x9F03, L"Amount, Other (Numeric)" },
    { 0x9F04, L"Amount, Other (Binary)" },
    { 0x9F05, L"Application Discretionary Data" },
    { 0x9F06, L"Application Identifier (AID), Terminal" },
    { 0x9F07, L"Application Usage Control (AUC)" },
    { 0x9F08, L"Application Version Number" },
    { 0x9F08, L"Application Version Number, Card" },
    { 0x9F09, L"Application Version Number" },
    { 0x9F09, L"Application Version Number, Terminal" },
    { 0x9F0B, L"Cardholder Name - Extended" },
    { 0x9F0D, L"Issuer Action Code - Default" },
    { 0x9F0E, L"Issuer Action Code - Denial" },
    { 0x9F0F, L"Issuer Action Code - Online" },
    { 0x9F10, L"Issuer Application Data (IAD)" },
    { 0x9F11, L"Issuer Code Table Index" },
    { 0x9F12, L"Application Preferred Name" },
    { 0x9F13, L"Last Online Application Transaction Counter (ATC) Register" },
    { 0x9F14, L"Lower Consecutive Offline Limit (LCOL)" },
    { 0x9F15, L"Merchant Category Code (MCC)" },
    { 0x9F16, L"Merchant Identifier" },
    { 0x9F17, L"Personal Identification Number (PIN) Try Counter" },
    { 0x9F18, L"Issuer Script Identifier" },
    { 0x9F19, L"Deleted (see 9F49)" },
    { 0x9F1A, L"Terminal Country Code" },
    { 0x9F1B, L"Terminal Floor Limit" },
    { 0x9F1C, L"Terminal Identification" },
    { 0x9F1D, L"Terminal Risk Management Data" },
    { 0x9F1E, L"Interface Device (IFD) Serial Number" },
    { 0x9F1F, L"Track 1 Discretionary Data" },
    { 0x9F1F, L"Track 1, Discretionary Data" },
    { 0x9F20, L"Track 2 Discretionary Data" },
    { 0x9F20, L"Track 2, Discretionary Data" },
    { 0x9F21, L"Transaction Time" },
    { 0x9F22, L"Certification Authority Public Key Index (PKI)" },
    { 0x9F22, L"Public Key Index, Certification Authority, Terminal" },
    { 0x9F23, L"Upper Consecutive Offline Limit (UCOL)" },
    { 0x9F24, L"Payment Account Reference (PAR) generated or linked directly to the provision request in the token vault" },
    { 0x9F26, L"Application Cryptogram (AC)" },
    { 0x9F27, L"Cryptogram Information Data (CID)" },
    { 0x9F29, L"Extended Selection" },
    { 0x9F2A, L"Kernel Identifier" },
    { 0x9F2D, L"Integrated Circuit Card (ICC) PIN Encipherment Public Key Certificate" },
    { 0x9F2E, L"Integrated Circuit Card (ICC) PIN Encipherment Public Key Exponent" },
    { 0x9F2F, L"Integrated Circuit Card (ICC) PIN Encipherment Public Key Remainder" },
    { 0x9F32, L"Issuer Public Key Exponent" },
    { 0x9F33, L"Terminal Capabilities" },
    { 0x9F34, L"Cardholder Verification Method (CVM) Results" },
    { 0x9F35, L"Terminal Type" },
    { 0x9F36, L"Application Transaction Counter (ATC)" },
    { 0x9F37, L"Unpredictable Number (UN) (Reader/Terminal)" },
    { 0x9F37, L"Unpredictable Number (UN)" },
    { 0x9F38, L"Processing Options Data Object List (PDOL)" },
    { 0x9F39, L"Point-of-Service (POS) Entry Mode" },
    { 0x9F3A, L"Amount, Reference Currency (Binary)" },
    { 0x9F3B, L"Currency Code, Application Reference" },
    { 0x9F3C, L"Currency Code, Transaction Reference" },
    { 0x9F3D, L"Currency Exponent, Transaction Reference" },
    { 0x9F40, L"Additional Terminal Capabilities (ATC)" },
    { 0x9F41, L"Transaction Sequence Counter" },
    { 0x9F42, L"Currency Code, Application" },
    { 0x9F43, L"Currency Exponent, Application Reference" },
    { 0x9F44, L"Currency Exponent, Application" },
    { 0x9F45, L"Data Authentication Code" },
    { 0x9F46, L"Application Public Key Certificate" },
    { 0x9F46, L"Integrated Circuit Card (ICC) Public Key Certificate" },
    { 0x9F47, L"Application Public Key Exponent" },
    { 0x9F47, L"Integrated Circuit Card (ICC) Public Key Exponent" },
    { 0x9F48, L"Application Public Key Remainder" },
    { 0x9F48, L"Integrated Circuit Card (ICC) Public Key Remainder" },
    { 0x9F49, L"Dynamic Data Authentication Data Object List (DDOL)" },
    { 0x9F4A, L"Static Data Authentication Tag List (SDA)" },
    { 0x9F4B, L"Signed Dynamic Application Data (SDAD)" },
    { 0x9F4C, L"ICC Dynamic Number" },
    { 0x9F4D, L"Log Entry" },
    { 0x9F4E, L"Merchant Name and Location" },
    { 0x9F4F, L"Log Format" },
    { 0x9F50, L"Cardholder Verification Status" },
    { 0x9F50, L"Offline Accumulator Balance" },
    { 0x9F51, L"Application Currency Code" },
    { 0x9F51, L"DRDOL" },
    { 0x9F52, L"Application Default Action (ADA)" },
    { 0x9F52, L"Terminal Compatibility Indicator" },
    { 0x9F53, L"Consecutive Transaction Counter International Limit (CTCIL)" },
    { 0x9F53, L"Terminal Interchange Profile (dynamic)" },
    { 0x9F53, L"Transaction Category Code" },
    { 0x9F54, L"Cumulative Total Transaction Amount Limit (CTTAL)" },
    { 0x9F54, L"DS ODS Card" },
    { 0x9F55, L"Geographic Indicator" },
    { 0x9F55, L"Issuer Authentication Flags" },
    { 0x9F56, L"Issuer Authentication Indicator" },
    { 0x9F56, L"Issuer Proprietary Bitmap" },
    { 0x9F57, L"Issuer Country Code" },
    { 0x9F58, L"Consecutive Transaction Counter Limit (CTCL)" },
    { 0x9F59, L"Consecutive Transaction Counter Upper Limit (CTCUL)" },
    { 0x9F5A, L"Application Program Identifier (Program ID)" },
    { 0x9F5B, L"DSDOL" },
    { 0x9F5B, L"Issuer Script Results" },
    { 0x9F5C, L"Cumulative Total Transaction Amount Upper Limit (CTTAUL)" },
    { 0x9F5C, L"DS Requested Operator ID" },
    { 0x9F5C, L"Magstripe Data Object List (MDOL)" },
    { 0x9F5D, L"Application Capabilities Information (ACI)" },
    { 0x9F5D, L"Available Offline Spending Amount (AOSA)" },
    { 0x9F5E, L"Consecutive Transaction International Upper Limit (CTIUL)" },
    { 0x9F5E, L"DS ID" },
    { 0x9F5F, L"DS Slot Availability" },
    { 0x9F5F, L"Offline Balance" },
    { 0x9F60, L"CVC3 (Track1)" },
    { 0x9F60, L"Issuer Update Parameter" },
    { 0x9F60, L"P3 Generated 3DES KEYS" },
    { 0x9F61, L"CVC3 (Track2)" },
    { 0x9F62, L"Encrypted PIN - ISO 95641 Format 0 (Thales P3 Format 01)" },
    { 0x9F62, L"PCVC3 (Track1)" },
    { 0x9F63, L"Offline Counter Initial Value" },
    { 0x9F63, L"PUNATC (Track1)" },
    { 0x9F64, L"NATC (Track1)" },
    { 0x9F65, L"PCVC3 (Track2)" },
    { 0x9F66, L"PUNATC (Track2)" },
    { 0x9F66, L"Terminal Transaction Qualifiers (TTQ)" },
    { 0x9F67, L"MSD Offset" },
    { 0x9F67, L"NATC (Track2)" },
    { 0x9F68, L"Card Additional Processes" },
    { 0x9F69, L"Card Authentication Related Data" },
    { 0x9F69, L"UDOL" },
    { 0x9F6A, L"Unpredictable Number (Numeric)" },
    { 0x9F6B, L"Card CVM Limit" },
    { 0x9F6B, L"Track 2 Data" },
    { 0x9F6C, L"Card Transaction Qualifiers (CTQ)" },
    { 0x9F6D, L"Kernel 4 Reader Capabilities" },
    { 0x9F6D, L"Mag-stripe Application Version Number (Reader)" },
    { 0x9F6D, L"VLP Reset Threshold" },
    { 0x9F6E, L"Form Factor Indicator (FFI)" },
    { 0x9F6E, L"Form Factor Indicator (qVSDC)" },
    { 0x9F6E, L"Third Party Data" },
    { 0x9F6F, L"DS Slot Management Control" },
    { 0x9F70, L"Card Interface Capabilities" },
    { 0x9F70, L"Protected Data Envelope 1" },
    { 0x9F71, L"Mobile CVM Results" },
    { 0x9F71, L"Protected Data Envelope 2" },
    { 0x9F72, L"Consecutive Transaction Limit (International—Country)" },
    { 0x9F72, L"Protected Data Envelope 3" },
    { 0x9F73, L"Currency Conversion Parameters" },
    { 0x9F73, L"Protected Data Envelope 4" },
    { 0x9F74, L"Protected Data Envelope 5" },
    { 0x9F74, L"VLP Issuer Authorisation Code" },
    { 0x9F75, L"Cumulative Total Transaction Amount Limit-Dual Currency" },
    { 0x9F75, L"Unprotected Data Envelope 1" },
    { 0x9F76, L"Secondary Application Currency Code" },
    { 0x9F76, L"Unprotected Data Envelope 2" },
    { 0x9F77, L"Unprotected Data Envelope 3" },
    { 0x9F77, L"VLP Funds Limit" },
    { 0x9F78, L"Unprotected Data Envelope 4" },
    { 0x9F78, L"VLP Single Transaction Limit" },
    { 0x9F79, L"Unprotected Data Envelope 5" },
    { 0x9F79, L"VLP Available Funds" },
    { 0x9F7A, L"VLP Terminal Support Indicator" },
    { 0x9F7B, L"VLP Terminal Transaction Limit" },
    { 0x9F7C, L"Customer Exclusive Data (CED)" },
    { 0x9F7C, L"Merchant Custom Data" },
    { 0x9F7D, L"DS Summary 1" },
    { 0x9F7D, L"VISA Applet Data" },
    { 0x9F7E, L"Application life cycle data (8 first bytes)" },
    { 0x9F7E, L"Mobile Support Indicator" },
    { 0x9F7F, L"Card Production Life Cycle (CPLC) Data" },
    { 0x9F7F, L"DS Unpredictable Number" },
    { 0xBF0C, L"File Control Information (FCI) Issuer Discretionary Data" },
    { 0xBF50, L"Visa Fleet - CDO" },
    { 0xBF60, L"Integrated Data Storage Record Update Template" },
    { 0x00C3, L"Card issuer action code -decline" },
    { 0x00C4, L"Card issuer action code -default" },
    { 0x00C5, L"Card issuer action code online" },
    { 0x00C6, L"PIN Try Limit" },
    { 0x00C7, L"CDOL 1 Related Data Length" },
    { 0x00C8, L"Card risk management country code" },
    { 0x00C9, L"Card risk management currency code" },
    { 0x00CA, L"Lower cummulative offline transaction amount" },
    { 0x00CB, L"Upper cumulative offline transaction amount" },
    { 0x00CD, L"Card Issuer Action Code (PayPass) - Default" },
    { 0x00CE, L"Card Issuer Action Code (PayPass) - Online" },
    { 0x00CF, L"Card Issuer Action Code (PayPass) - Decline" },
    { 0x00D1, L"Currency conversion table" },
    { 0x00D2, L"Integrated Data Storage Directory (IDSD)" },
    { 0x00D3, L"Additional check table" },
    { 0x00D5, L"Application Control" },
    { 0x00D6, L"Default ARPC response code" },
    { 0x00D7, L"Application Control (PayPass)" },
    { 0x00D8, L"AIP (PayPass)" },
    { 0x00D9, L"AFL (PayPass)" },
    { 0x00DA, L"Static CVC3-TRACK1" },
    { 0x00DB, L"Static CVC3-TRACK2" },
    { 0x00DC, L"IVCVC3-TRACK1" },
    { 0x00DD, L"IVCVC3-TRACK2" },
    { 0xDF01, L"Encrypted PIN Block in Tag 9F62 - ISO 95641 Format 0" },
    { 0xDF02, L"PEK Version Number" },
    { 0xDF03, L"PIN Try Limit" },
    { 0xDF04, L"PIN Try Counter (VSDC Application)" },
    { 0xDF05, L"AIP - For VISA Contactless" },
    { 0xDF06, L"Products permitted" },
    { 0xDF07, L"Offline checks mandated" },
    { 0xDF08, L"UDKmac" },
    { 0xDF09, L"UDKenc" },
    { 0xDF0B, L"Retries Permitted Limit" },
    { 0xDF0C, L"Script Message Update" },
    { 0xDF0D, L"Fleet Issuer Action Code - Default" },
    { 0xDF0E, L"Fleet Issuer Action Code - Denial" },
    { 0xDF0F, L"Fleet Issuer Action Code - Online" },
    { 0xDF12, L"Vehicle Registration Number" },
    { 0xDF13, L"DDA Public Modulus" },
    { 0xDF14, L"Driver Name" },
    { 0xDF15, L"Driver ID" },
    { 0xDF16, L"Max Fill Volume" },
    { 0xDF17, L"DDA Public Modulus Length" },
    { 0xDF18, L"Mileage" },
    { 0xDF20, L"Issuer Proprietary Bitmap (IPB)" },
    { 0xDF21, L"Internet Authentication Flag (IAF)" },
    { 0xDF22, L"Encrypted PEK - RFU" },
    { 0xDF23, L"PEK Key Check Value - RFU" },
    { 0xDF24, L"MDK - Key derivation Index" },
    { 0xDF25, L"VISA DPA - MDK - Key derivation Index" },
    { 0xDF26, L"Encrypted PIN Block - ISO 9564-1 Format 1 PIN Block (Thales P3 Format 05)" },
    { 0xDF40, L"qVSDC AIP" },
    { 0xDF41, L"VSDC AIP" },
    { 0xDF42, L"UDKac" },
    { 0xDF43, L"UDKmac" },
    { 0xDF44, L"UDKenc" },
    { 0xDF47, L"UDKcvc" },
    { 0xDF48, L"UDKac KCV" },
    { 0xDF49, L"UDKmac KCV" },
    { 0xDF4A, L"UDKenc KCV" },
    { 0xDF4B, L"POS Cardholder Interaction Information" },
    { 0xDF4B, L"UDKcvc KCV" },
    { 0xDF51, L"Grand Parent AC" },
    { 0xDF52, L"Parent AC" },
    { 0xDF53, L"Grand Parent MAC" },
    { 0xDF54, L"Parent MAC" },
    { 0xDF55, L"Grand Parent ENC" },
    { 0xDF56, L"Parent ENC/Terminal Action Code - Default" },
    { 0xDF57, L"Terminal Action Code - Decline" },
    { 0xDF60, L"DDA Component P" },
    { 0xDF60, L"DS Input (Card)" },
    { 0xDF61, L"DDA Component Q" },
    { 0xDF61, L"DS Digest H" },
    { 0xDF62, L"DDA Component D1" },
    { 0xDF62, L"DS ODS Info" },
    { 0xDF63, L"DDA Component D2" },
    { 0xDF63, L"DS ODS Term" },
    { 0xDF64, L"DDA Component Q Minus 1 Mod P" },
    { 0xDF65, L"DDA Private Exponent" },
    { 0xDF6B, L"Paypass Contactless" },
    { 0xDF79, L"Dynamic Data Authentication Keys" },
};

std::wstring const Tag::name_unknown_ = L"Unknown tag";

Tag::Tag(unsigned char const *buffer) {
    tag_.push_back(*buffer);
    if ((*buffer & MASK_TAG_NUMBER_0) == MULTI_BYTE_TAG) {
        do {
            buffer++;
            tag_.push_back(*buffer);
        } while (tag_.back() & MASK_TAG_NEXT_BYTE);
    }
    tag_.shrink_to_fit();
}

Tag::Tag(uint16_t tag) {
    if (tag & 0xFF00) {
        tag_.push_back(static_cast<unsigned char>(tag >> 8));
    }
    tag_.push_back(static_cast<unsigned char>(tag & 0xFF));
}

uintptr_t Tag::number() const noexcept {
    if ((tag_[0] & MASK_TAG_NUMBER_0) != MULTI_BYTE_TAG) {
        return tag_[0] & MASK_TAG_NUMBER_0;
    }
    // Multi byte tag
    uintptr_t number = tag_[1] & MASK_TAG_NUMBER_N;
    for (size_t i = 1; tag_[i] & MASK_TAG_NEXT_BYTE; ) {
        i++;
        number <<= NUMBER_BITS;
        number |= tag_[i] & MASK_TAG_NUMBER_N;
    }
    return number;
}

uintptr_t Tag::value() const noexcept {
    uintptr_t result = 0;
    for (auto b : tag_) {
        result <<= 8;
        result |= b;
    }
    return result;
}

std::wstring const& rsc::Tag::name() const noexcept {
    if (auto name = name_map_.find(static_cast<uint16_t>(value())); name != name_map_.end())
        return name->second;
    else
        return name_unknown_;
}
