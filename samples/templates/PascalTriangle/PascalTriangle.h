#pragma once

template <typename T>
class PascalTriangleGenerator
{
public:
	using ValueType = T;
	using RowType = std::vector<ValueType>;

	const RowType& GetRow(unsigned index) const&
	{
		CreateRows(index + 1);
		return m_rows.at(index);
	}
	const RowType& GetRow(unsigned) const&& = delete;

private:
	void CreateRows(unsigned numRows) const
	{
		if (m_rows.size() < numRows)
		{
			m_rows.reserve(numRows);
			for (unsigned row = static_cast<unsigned>(m_rows.size()); row < numRows; ++row)
			{
				m_rows.emplace_back(GenerateRow(row));
			}
		}
	}
	RowType GenerateRow(unsigned rowIndex) const
	{
		if (rowIndex == 0)
		{
			return { 1 };
		}
		RowType row;
		row.reserve(rowIndex + 1);
		ValueType leftUpValue = 0;
		const RowType& prevRow = m_rows.at(rowIndex - 1);
		for (unsigned i = 0; i < rowIndex; ++i)
		{
			const ValueType& rightUpValue = prevRow.at(i);
			row.emplace_back(leftUpValue + rightUpValue);
			leftUpValue = rightUpValue;
		}
		row.emplace_back(leftUpValue);
		return row;
	}

	mutable std::vector<RowType> m_rows;
};
