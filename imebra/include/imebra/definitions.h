/*

Imebra 4.0.7.1 changeset 108a911a22e1

Imebra: a C++ Dicom library

Copyright (c) 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016
by Paolo Brandoli/Binarno s.p.

All rights reserved.

This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License version 2 as published by
 the Free Software Foundation.

This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

-------------------

If you want to use Imebra commercially then you have to buy the commercial
 license available at http://imebra.com

After you buy the commercial license then you can use Imebra according
 to the terms described in the Imebra Commercial License.
A copy of the Imebra Commercial License is available at http://imebra.com.

Imebra is available at http://imebra.com

The author can be contacted by email at info@binarno.com or by mail at
 the following address:
 Binarno s.p., Paolo Brandoli
 Rakuseva 14
 1000 Ljubljana
 Slovenia



*/

/*! \file definitions.h
    \brief Declaration of the enumeration classes and custom types.
*/

#if !defined(imebraDefinitions__INCLUDED_)
#define imebraDefinitions__INCLUDED_

#include <cstdint>
#include <vector>
#include <string>

#ifndef SWIG

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
  #define IMEBRA_HELPER_DLL_IMPORT __declspec(dllimport)
  #define IMEBRA_HELPER_DLL_EXPORT __declspec(dllexport)
#else
  #if __GNUC__ >= 4
    #define IMEBRA_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define IMEBRA_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
  #else
    #define IMEBRA_HELPER_DLL_IMPORT
    #define IMEBRA_HELPER_DLL_EXPORT
  #endif
#endif

// IMEBRA_API is used for the public API symbols

#ifdef IMEBRA_DLL // defined if Imebra is compiled as a DLL
  #ifdef IMEBRA_DLL_EXPORTS // defined if we are building the Imebra DLL (instead of using it)
    #define IMEBRA_API IMEBRA_HELPER_DLL_EXPORT
  #else
    #define IMEBRA_API IMEBRA_HELPER_DLL_IMPORT
  #endif // IMEBRA_DLL_EXPORTS
#else // IMEBRA_DLL is not defined: this means Imebra is a static lib.
  #define IMEBRA_API
#endif // IMEBRA_DLL

#endif // SWIG

namespace imebra
{

///
/// \brief Used by setAge() and getAge() to specify the unit of the age value.
///
///////////////////////////////////////////////////////////////////////////////
enum class ageUnit_t: char
{
    days = 'D',   ///< the age value is in days
    weeks = 'W',  ///< the age value is in weeks
    months = 'M', ///< the age value is in months
    years = 'Y'   ///< the age value is in years
};


///
///
/// \brief This enumeration specifies the quality of the compressed image
///        when a lossy compression format is used.
///
///////////////////////////////////////////////////////////////////////////////
enum class imageQuality_t: std::uint32_t
{
    veryHigh = 0,      ///< the image is saved with very high quality. No subsampling is performed and no quantization
    high = 100,        ///< the image is saved with high quality. No subsampling is performed. Quantization ratios are low
    aboveMedium = 200, ///< the image is saved in medium quality. Horizontal subsampling is applied. Quantization ratios are low
    medium = 300,      ///< the image is saved in medium quality. Horizontal subsampling is applied. Quantization ratios are medium
    belowMedium = 400, ///< the image is saved in medium quality. Horizontal and vertical subsampling are applied. Quantization ratios are medium
    low = 500,         ///< the image is saved in low quality. Horizontal and vertical subsampling are applied. Quantization ratios are higher than the ratios used in the belowMedium quality
    veryLow = 600	   ///< the image is saved in low quality. Horizontal and vertical subsampling are applied. Quantization ratios are high
};


///
/// \brief Defines the size (in bytes) of the memory allocated for each
///        pixel's color component and its representation (signed/unsigned).
///
/// This enumeration does not specify the highest bit used:
/// in order to retrieve the highest used bit call Image::getHighBit().
///
///////////////////////////////////////////////////////////////////////////////
enum class bitDepth_t: std::uint32_t
{
    depthU8 = 0,    ///< Unsigned byte
    depthS8 = 1,    ///< Signed byte
    depthU16 = 2,   ///< Unsigned word (2 bytes)
    depthS16 = 3,   ///< Signed word (2 bytes)
    depthU32 = 4,   ///< Unsigned double word (4 bytes)
    depthS32 = 5    ///< Signed double word (4 bytes)
};


///
/// \brief Specifies the directory item's type.
///
///////////////////////////////////////////////////////////////////////////////
enum class directoryRecordType_t: std::uint32_t
{
    patient,
    study,
    series,
    image,
    overlay,
    modality_lut,
    voi_lut,
    curve,
    topic,
    visit,
    results,
    interpretation,
    study_component,
    stored_print,
    rt_dose,
    rt_structure_set,
    rt_plan,
    rt_treat_record,
    presentation,
    waveform,
    sr_document,
    key_object_doc,
    spectroscopy,
    raw_data,
    registration,
    fiducial,
    mrdr,
    endOfDirectoryRecordTypes
};


///
/// \brief Defines the data stream & images codec.
///
///////////////////////////////////////////////////////////////////////////////
enum class codecType_t: std::uint32_t
{
    dicom, ///< DICOM codec
    jpeg   ///< JPEG codec
};

#define MAKE_VR_ENUM(string) ((std::uint16_t)((((std::uint16_t)string[0]) << 8) | (std::uint16_t)string[1]))

/// \brief Enumerates the DICOM VRs (data types).
///
///////////////////////////////////////////////////////////////////////////////
enum class tagVR_t: std::uint32_t
{
    AE = 0x4145, ///< Application Entity
    AS = 0x4153, ///< Age String
    AT = 0x4154, ///< Attribute Tag
    CS = 0x4353, ///< Code String
    DA = 0x4441, ///< Date
    DS = 0x4453, ///< Decimal String
    DT = 0x4454, ///< Date Time
    FL = 0x464c, ///< Floating Point Single
    FD = 0x4644, ///< Floating Point Double
    IS = 0x4953, ///< Integer String
    LO = 0x4c4f, ///< Long String
    LT = 0x4c54, ///< Long Text
    OB = 0x4f42, ///< Other Byte String
    SB = 0x5342, ///< Non standard. Used internally for signed bytes
    OD = 0x4f44, ///< Other Double String
    OF = 0x4f46, ///< Other Float String
    OL = 0x4f4c, ///< Other Long String
    OW = 0x4f57, ///< Other Word String
    PN = 0x504e, ///< Person Name
    SH = 0x5348, ///< Short String
    SL = 0x534c, ///< Signed Long
    SQ = 0x5351, ///< Sequence of Items
    SS = 0x5353, ///< Signed Short
    ST = 0x5354, ///< Short Text
    TM = 0x544d, ///< Time
    UC = 0x5543, ///< Unlimited characters
    UI = 0x5549, ///< Unique Identifier
    UL = 0x554c, ///< Unsigned Long
    UN = 0x554e, ///< Unknown
    UR = 0x5552, ///< Unified Resource Identifier
    US = 0x5553, ///< Unsigned Short
    UT = 0x5554  ///< Unlimited Text
};

#ifndef SWIG
static_assert((std::uint16_t)tagVR_t::AE == MAKE_VR_ENUM("AE"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::AS == MAKE_VR_ENUM("AS"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::AT == MAKE_VR_ENUM("AT"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::CS == MAKE_VR_ENUM("CS"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::DA == MAKE_VR_ENUM("DA"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::DS == MAKE_VR_ENUM("DS"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::DT == MAKE_VR_ENUM("DT"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::FL == MAKE_VR_ENUM("FL"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::FD == MAKE_VR_ENUM("FD"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::IS == MAKE_VR_ENUM("IS"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::LO == MAKE_VR_ENUM("LO"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::LT == MAKE_VR_ENUM("LT"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::OB == MAKE_VR_ENUM("OB"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::SB == MAKE_VR_ENUM("SB"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::OD == MAKE_VR_ENUM("OD"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::OF == MAKE_VR_ENUM("OF"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::OL == MAKE_VR_ENUM("OL"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::OW == MAKE_VR_ENUM("OW"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::PN == MAKE_VR_ENUM("PN"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::SH == MAKE_VR_ENUM("SH"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::SL == MAKE_VR_ENUM("SL"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::SQ == MAKE_VR_ENUM("SQ"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::SS == MAKE_VR_ENUM("SS"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::ST == MAKE_VR_ENUM("ST"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::TM == MAKE_VR_ENUM("TM"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::UC == MAKE_VR_ENUM("UC"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::UI == MAKE_VR_ENUM("UI"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::UL == MAKE_VR_ENUM("UL"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::UN == MAKE_VR_ENUM("UN"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::UR == MAKE_VR_ENUM("UR"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::US == MAKE_VR_ENUM("US"), "Wrong VR enumeration value");
static_assert((std::uint16_t)tagVR_t::UT == MAKE_VR_ENUM("UT"), "Wrong VR enumeration value");
#endif


typedef std::vector<std::string> fileParts_t;

typedef std::vector<std::string> charsetsList_t;


///
/// \brief Defines the type of the bitmap generated by DrawBitmap.
///
///////////////////////////////////////////////////////////////////////////////
enum class drawBitmapType_t: std::uint32_t
{
    drawBitmapRGB  = 0, ///< Generates a BMP image where each pixel contains 3 bytes (R, G and B)
    drawBitmapBGR  = 1, ///< Generates a BMP image where each pixel contains 3 bytes (B, G and R)
    drawBitmapRGBA = 2, ///< Generates a BMP image where each pixel contains 4 bytes (R, G, B and A)
    drawBitmapBGRA = 3  ///< Generates a BMP image where each pixel contains 4 bytes (B, G, R and A)
};


///
/// \brief Specifies an age, in days, weeks, months or years.
///
///////////////////////////////////////////////////////////////////////////////
struct IMEBRA_API Age
{
    /// \brief Constructor.
    ///
    /// \param initialAge the initial age to assign to the object, in days, weeks,
    ///                   months or years, depending on the parameter initialUnits
    /// \param initialUnits the units of the value in initialAge
    ///
    ///////////////////////////////////////////////////////////////////////////////
    Age(std::uint32_t initialAge, ageUnit_t initialUnits);

    /// \brief Return the age in years.
    ///
    /// \return the stored age converted to years.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    double years() const;

    std::uint32_t age;   ///< The age, in days, weeks, months or years according to units
    ageUnit_t     units; ///< The units of the value in age

};


///
/// \brief Stores a Date, Time or Date/Time value.
///
///////////////////////////////////////////////////////////////////////////////
struct IMEBRA_API Date
{
    /// \brief Constructor.
    ///
    /// Initialize the Date structure with the specified values.
    ///
    /// \param initialYear    year (0 = unused)
    /// \param initialMonth   month (1...12, 0 = unused)
    /// \param initialDay     day of the month (1...31, 0 = unused)
    /// \param initialHour    hour (0...23)
    /// \param initialMinutes minutes (0...59)
    /// \param initialSeconds seconds (0...59)
    /// \param initialNanoseconds nanoseconds
    /// \param initialOffsetHours   hours offset from UTC
    /// \param initialOffsetMinutes minutes offset from UTC
    ///////////////////////////////////////////////////////////////////////////////
    Date(const std::uint32_t initialYear,
         const std::uint32_t initialMonth,
         const std::uint32_t initialDay,
         const std::uint32_t initialHour,
         const std::uint32_t initialMinutes,
         const std::uint32_t initialSeconds,
         const std::uint32_t initialNanoseconds,
         const std::int32_t initialOffsetHours,
         const std::int32_t initialOffsetMinutes);

    std::uint32_t year;         ///< Year (0 = unused)
    std::uint32_t month;        ///< Month (1...12, 0 = unused)
    std::uint32_t day;          ///< Day (1...12, 0 = unused)
    std::uint32_t hour;         ///< Hours
    std::uint32_t minutes;      ///< Minutes
    std::uint32_t seconds;      ///< Seconds
    std::uint32_t nanoseconds;  ///< Nanoseconds
    std::int32_t offsetHours;   ///< Offset hours from UTC
    std::int32_t offsetMinutes; ///< Offset minutes from UTC

};

///
/// \brief Stores a VOI Description and Settings
///
/// The VOI settings can be retrieved from a DataSet with DataSet::getVOIs(),
/// which returns all the VOI settings registered in the DataSet.
///
/// Once retrieved, the VOI center and width can be passed to the VOILUT
/// transform that apply the VOI settings to an Image.
///
///////////////////////////////////////////////////////////////////////////////
struct IMEBRA_API VOIDescription
{
    double center;            ///< The VOI center
    double width;             ///< The VOI width
    std::wstring description; ///< The VOI's description
};

/// \brief A collection of VOI settings.
///
/// The VOI settings registered in the dataset can be retrieved with
/// DataSet::getVOIs().
///
///////////////////////////////////////////////////////////////////////////////
typedef std::vector<VOIDescription> vois_t;

} // namespace imebra

#endif // imebraDefinitions__INCLUDED_
