#pragma once

// Сигнатура PNG-файла (первые 8 байт)
// http://www.w3.org/TR/PNG/#5PNG-file-signature
static const uint8_t PNG_SIGNATURE[] = { 137, 80, 78, 71, 13, 10, 26, 10 };

// Чанк заголовка изображения
// http://www.w3.org/TR/PNG/#11IHDR
static const uint8_t IHDR_SIGNATURE[] = { 73, 72, 68, 82 };

enum class PngColorType : uint8_t
{
	Greyscale = 0,
	Truecolor = 2,
	Indexed = 3,
	GreyscaleWithAlpha = 4,
	TrueColorWithAlpha = 6
};

enum class PngInterlaceMethod : uint8_t
{
	NoInterlace = 0,
	Adam7 = 1,
};

// Директива #pragma pack, специфичная для Visual C++, позволяет управлять
// выравниванием данных внутри стуктур
// По умолчанию компилятор C/C++ волен выравнивать поля в структуре (кроме первого) так, чтобы обеспечить
// наилучшую эффективность при работе с ними, что может привести к несоответствию 
// размещения полей в структуре
//
// С помощью #pragma pack все поля внутри структур, связанных с заголовком PNG-файла 
// выровнены по границам 1 байта, что обеспечивает идентичное размещение структуры
#pragma pack (push) // Запомнили текущий режим выравнивания
#pragma pack(1) // Включили выравнивание полей структур по границам байтов
struct ChunkHeader
{
	uint32_t chunkSize;
	uint8_t signature[sizeof(IHDR_SIGNATURE)];
};
struct IHDRChunk : ChunkHeader
{
	uint32_t width;
	uint32_t height;
	uint8_t bitDepth;
	PngColorType colorType;
	uint8_t compressionMethod; // должен быть равен 0
	uint8_t filterMethod; // должен быть равен 0
	PngInterlaceMethod interlaceMethod;
};
struct PNGInfo
{
	uint8_t pngSignature[sizeof(PNG_SIGNATURE)];
	IHDRChunk imageHeader;
};
#pragma pack (pop) // Восстановили текущий режим выравнивания полей структур
