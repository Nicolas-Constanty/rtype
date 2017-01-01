//
// Created by gaspar_q on 11/30/16.
//

#ifndef RTYPE_RECEPTIONSTATUS_HPP
#define RTYPE_RECEPTIONSTATUS_HPP

#include <stdexcept>
#include <fstream>
#include <iostream>

#include <limits>

namespace Network
{
    namespace UDP
    {
        /**
         * @brief Class that is used to store receptions of udp packets
         * @tparam SequenceType The type of the sequence id
         * @tparam StatusType The type of the status stored inside
         */
        template <typename SequenceType, typename StatusType = SequenceType>
        class PREF_EXPORT ReceptionStatus
        {
        public:
            /**
             * @brief Basic constructor
             */
            ReceptionStatus() :
                    sequenceId(0),
                    status(0),
                    isSet(false)
            {

            }

            /**
             * @brief Basic copy constructor
             * @param ref The reference to copy
             */
            ReceptionStatus(ReceptionStatus<SequenceType, StatusType> const &ref) :
                    sequenceId(ref.sequenceId),
                    status(ref.status),
                    isSet(ref.isSet)
            {

            }

            /**
             * @brief Basic constructor
             */
            ~ReceptionStatus()
            {

            }

        public:
            /**
             * @brief Basic copy operator
             * @param ref The reference to copy
             * @return A reference on <this>
             */
            ReceptionStatus<SequenceType, StatusType> &operator=(ReceptionStatus<SequenceType, StatusType> const &ref)
            {
                sequenceId = ref.sequenceId;
                status = ref.status;
                return *this;
            }

        public:
            /**
             * @brief Tells to the status that we received a packet with its sequence id
             * @param packetSeq The sequence id of the packet
             * @return True if the packet have been set, false either
             */
            bool Receiving(SequenceType packetSeq)
            {
                if (!isSet)
                {
                    isSet = true;
                    sequenceId = packetSeq;
                    return setReceived(packetSeq);
                }
                if (IsMoreRecent(packetSeq))
                {
                    SequenceType save = sequenceId;

                    sequenceId = packetSeq;
                    int index = getSeqId(save);

                    if (index < 0)
                        status = 0;
                    else
                    {
                        status = status >> (-index + sizeof(StatusType) * 8 - 1);
                        return setReceived(sequenceId);
                    }
                }
                else
                    return setReceived(packetSeq);
                return true;
            }

            /**
             * @brief Allow user to check if the packet is actually set in the buffer
             * @param packetSeq The sequence id to check
             * @return True if the packet is set inside the status, false either
             */
            bool IsSet(SequenceType packetSeq) const
            {
                if (!isSet)
                {
//                    std::cout << "Status not set" << std::endl;
                    return false;
                }
                int index = getSeqId(packetSeq);

//                std::cout << "Index of " << packetSeq << " = " << index << std::endl;
                if (index < 0)
                    return false;
                return packetSeq == sequenceId || (status & (1 << index));
            }

            /**
             * @brief Returns the status that tells
             * @return The internal status
             */
            StatusType getStatus() const
            {
                return status;
            }

            /**
             * @brief Sets the internal status
             * @param stat The status to set
             */
            void setStatus(StatusType stat)
            {
                status = stat;
            }

            /**
             * @brief Returns the Status from a specific sequence id. The size returned is the sizeof SequenceId
             * @param sequenceid The sequence id from how
             * @return
             */
            ReceptionStatus<SequenceType> sliceAt(SequenceType sequenceid)
            {
                ReceptionStatus<SequenceType>   stat;
                int index = getSeqId(sequenceid);

                if (index < 0 || index < static_cast<int>((sizeof(StatusType) - sizeof(SequenceType)) * 8))
                    return stat;
                stat.Receiving(sequenceid);
                stat.setStatus((status >> (index - sizeof(SequenceType) * 8 + 1)) & (SequenceType)-1);
                return stat;
            }

            void reset()
            {
                status = 0;
                isSet = false;
                sequenceId = 0;
            }

        private:
            /**
             * @brief Checks if the sequence id the is more recent than the current sequence id
             * @param seqToCmp The sequence id to compare
             * @return True if <seqToCmp> is actually more recent thant the internal one
             */
            bool IsMoreRecent(SequenceType seqToCmp) const
            {
                return ((seqToCmp > sequenceId && seqToCmp - sequenceId <= std::numeric_limits<SequenceType>::max() / 2)
                        || (sequenceId > seqToCmp && sequenceId - seqToCmp > std::numeric_limits<SequenceType>::max() / 2));
            }

            /**
             * @brief Allow user to get the index of the bit where sequence id <seq> is stored
             * @param seq The sequence id to find
             * @return The index of the bit of the sequence id
             */
            int getSeqId(SequenceType seq) const
            {
                int index;

                if (seq > sequenceId)
                    index = std::numeric_limits<SequenceType>::max() - seq + sequenceId;
                else
                    index = sequenceId - seq;
                if (index < 0 || index > static_cast<int>(sizeof(StatusType) * 8))
                    return -1;
                return sizeof(StatusType) * 8 - index - 1;
            }

            /**
             * @brief Set the sequence id <seq> to 1 in internal buffer in order to say that we receive the packet
             * @param seq The sequence id to set to 1
             * @return True if the packet have been set, false either
             */
            bool setReceived(SequenceType seq)
            {
                int index = getSeqId(seq);
                if (index < 0)
                    return false;
                status |= (1 << index);
                return true;
            }

        public:
            /**
             * @brief Prints the status into a specific output
             * @param output The output in which print the status
             * @return A reference on <output>
             */
            std::ostream    &print(std::ostream &output) const
            {
                output << "(" << sequenceId << ")";
                for (int i = (sizeof(StatusType) * 8) - 1; i >= 0; --i)
                {
                    output << static_cast<int>((status & (1 << i)) != 0);
                }
                return output;
            }

        private:
            SequenceType sequenceId;
            StatusType status;
            bool isSet;
        };

        /**
         * @brief Operator shift on output allow user to print a status inside a stream
         * @tparam T The type of the status
         * @param output The output in which print the status
         * @param todisp The status to print
         * @return A reference on <output>
         */
        template <typename T, typename I>
        std::ostream    &operator<<(std::ostream &output, ReceptionStatus<T, I> const &todisp)
        {
            return todisp.print(output);
        }
    }
}

#endif //RTYPE_RECEPTIONSTATUS_HPP
